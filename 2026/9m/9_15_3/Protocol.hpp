#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <functional>
#include "Socket.hpp"

using namespace SocketModule;

// client -> server
class Request
{
public:
    Request()
    {
    }

    Request(int x, int y, char oper)
        : _x(x),
          _y(y),
          _oper(oper)
    {
    }

    std::string Serialize()
    {
        Json::Value root;
        root["x"] = _x;
        root["y"] = _y;
        root["oper"] = _oper;

        Json::FastWriter writer;
        std::string s = writer.write(root);
        return s;
    }

    bool Deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader;
        bool ok = reader.parse(in, root);
        if (ok)
        {
            _x = root["x"].asInt();
            _y = root["y"].asInt();
            _oper = root["oper"].asInt();
        }
        return ok;
    }

    int X()
    {
        return _x;
    }
    int Y()
    {
        return _y;
    }
    char Oper()
    {
        return _oper;
    }

    ~Request()
    {
    }

private:
    int _x;
    int _y;
    char _oper;
};

// server -> client
class Response
{
public:
    Response()
    {
    }

    Response(int result, int code)
        : _result(result),
          _code(code)
    {
    }

    std::string Serialize()
    {
        Json::Value root;
        root["result"] = _result;
        root["code"] = _code;

        Json::FastWriter writer;
        return writer.write(root);
    }

    bool Deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader;

        bool ok = reader.parse(in, root);
        if (ok)
        {
            _result = root["result"].asInt();
            _code = root["code"].asInt();
        }

        return ok;
    }

    void SetResult(int res)
    {
        _result = res;
    }

    void SetCode(int code)
    {
        _code = code;
    }

    ~Response()
    {
    }

private:
    int _result; // 运算结果
    int _code;   // 运算结果退出码
};

const std::string sep = "\r\n";

using func_t = std::function<Response(const Request &req)>;

class Protocol
{
public:
    Protocol(func_t func) : _func(func)
    {
    }

    std::string Encode(const std::string jsonstr)
    {
        std::string len = std::to_string(jsonstr.size());
        return len + sep + jsonstr + sep;
    }

    // 判断报文完整性，若包至少包含一个完整请求，提取并移除
    bool Decode(std::string &buffer, std::string *package)
    {
        ssize_t pos = buffer.find(sep);
        if (pos == std::string::npos)
            return false; // 让调用方回内核继续读取数据

        std::string package_len_str = buffer.substr(0, pos);
        int package_len_int = std::stoi(package_len_str);
        int target_len = package_len_str.size() + package_len_int + 2 * sep.size();

        if (buffer.size() < target_len)
        {
            return false;
        }

        // 到此至少有一个完整报文
        *package = buffer.substr(pos + sep.size(), package_len_int);
        buffer.erase(0, target_len);
        return true;
    }

    void GetRequest(std::shared_ptr<Socket> &sock, InetAddr &client)
    {
        std::string buffer_queue;
        while (true)
        {
            int n = sock->Recv(&buffer_queue);
            if (n > 0)
            {
                // 1. 解析报文，提取完整的json请求，若不完整继续读取
                std::string json_package;
                bool ret = Decode(buffer_queue, &json_package);
                if (!ret)
                    continue;

                // 2. 请求json串，反序列化
                Request req;
                bool ok = req.Deserialize(json_package);
                if (!ok)
                    continue;

                // 3. 计算
                Response resp = _func(req);

                // 4. 序列化
                std::string json_str = resp.Serialize();

                // 5. 添加自定义长度
                std::string send_str = Encode(json_str);

                // 6. 直接发送
                sock->Send(send_str);
            }
            else if (n == 0)
            {
                LOG(LogLevel::INFO) << "client:" << client.StringAddr() << "Quit!";
                break;
            }
            else
            {
                LOG(LogLevel::WARNING) << "client:" << client.StringAddr() << ",recv error";
                break;
            }
        }
    }

    ~Protocol()
    {
    }

private:
    Request _req;
    Response _resp;

    func_t _func;
};