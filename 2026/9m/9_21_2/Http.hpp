#pragma once

#include "Socket.hpp"
#include "TcpServer.hpp"
#include "Util.hpp"
#include "Log.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <unordered_map>

using namespace SocketModule;
using namespace LogModule;

const std::string gspace = " ";
const std::string glinespace = "\r\n";
const std::string glinesep = ": ";

const std::string webroot = "./wwwroot";
const std::string homepage = "/index.html";
const std::string page_404 = "/404.html";

class HttpRequest
{
public:
    HttpRequest() : _blankline(glinespace)
    {
    }

    std::string Serialize()
    {
        return std::string();
    }

    void PraseReqLine(std::string &reqline)
    {
        std::stringstream ss(reqline);
        ss >> _method >> _uri >> _version;
    }

    bool Deserialize(std::string &reqstr)
    {
        // 1. 提取请求行
        std::string reqline;
        bool res = Util::ReadOneLine(reqstr, &reqline, glinespace);

        // 2. 对请求行进行反序列化
        PraseReqLine(reqline);

        LOG(LogLevel::DEBUG) << "_method: " << _method;
        LOG(LogLevel::DEBUG) << "_uri: " << _uri;
        LOG(LogLevel::DEBUG) << "_version: " << _version;

        if (_uri == "/")
            _uri = webroot + _uri + homepage;
        else
            _uri = webroot + _uri;

        return true;
    }

    std::string Uri()
    {
        return _uri;
    }

    ~HttpRequest()
    {
    }

private:
    std::string _method;
    std::string _uri;
    std::string _version;

    std::unordered_map<std::string, std::string> _headers;
    std::string _blankline;
    std::string _text;
};

class HttpResponse
{
public:
    HttpResponse() : _blankline(glinespace)
    {
    }

    std::string Serialize()
    {
        std::string status_line = _version + gspace + std::to_string(_code) + gspace + _desc + glinespace;
        std::string resp_header;
        for (auto &header : _headers)
        {
            std::string line = header.first + glinesep + header.second + glinespace;
            resp_header += line;
        }

        return status_line + resp_header + _blankline + _text;
    }

    void SetTargetFile(const std::string &target)
    {
        _targetfile = target;
    }

    void SetCode(int code)
    {
        _code = code;
        switch (_code)
        {
        case 200:
            _desc = "OK";
            break;
        case 404:
            _desc = "Not Found";
            break;
        default:
            break;
        }
    }

    void SetHeader(const std::string &key, const std::string &value)
    {
        auto iter = _headers.find(key);
        if (iter != _headers.end())
        {
            return;
        }
        _headers.insert(std::make_pair(key, value));
    }

    bool MakeResponse()
    {
        int filesize = 0;
        bool res = Util::ReadFileContent(_targetfile, &_text);
        if (!res)
        {
            LOG(LogLevel::WARNING) << "client want get : " << _targetfile << "but not found";
            SetCode(404);
            _targetfile = webroot + page_404;
            filesize = Util::FileSize(_targetfile);
            Util::ReadFileContent(_targetfile, &_text);
        }
        else
        {
            SetCode(200);
            filesize = Util::FileSize(_targetfile);
        }
        SetHeader("Content-Length", std::to_string(filesize));
        return true;
    }

    bool Deserialize(std::string &reqstr)
    {
        return true;
    }

    ~HttpResponse()
    {
    }

public:
    std::string _version;
    int _code;
    std::string _desc;

    std::unordered_map<std::string, std::string> _headers;
    std::string _blankline;
    std::string _text;

    // 其他属性
    std::string _targetfile;
};

class Http
{
public:
    Http(uint16_t port) : tsvrp(std::make_unique<TcpServer>(port))
    {
    }

    void HandlerHttpRquest(std::shared_ptr<Socket> &sock, InetAddr &client)
    {
        std::string httpreqstr;
        int n = sock->Recv(&httpreqstr);

        if (n > 0)
        {
            HttpRequest req;
            req.Deserialize(httpreqstr);

            HttpResponse resp;
            resp.SetTargetFile(req.Uri());
            resp.MakeResponse(); // 真正读取文件内容

            std::string response_str = resp.Serialize();
            sock->Send(response_str);
        }
    }

    void Start()
    {
        tsvrp->Start([this](std::shared_ptr<Socket> &sock, InetAddr &client)
                     { this->HandlerHttpRquest(sock, client); });
    }

    ~Http()
    {
    }

private:
    std::unique_ptr<TcpServer> tsvrp;
};
