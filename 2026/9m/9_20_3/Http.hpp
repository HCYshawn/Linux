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

            std::string filename = req.Uri();
            HttpResponse resp;
            resp._version = "HTTP/1.1";
            resp._code = 200;
            resp._desc = "OK";

            bool res = Util::ReadFileContent(filename, &(resp._text));
        }

        // std::string httpreqstr;
        // sock->Recv(&httpreqstr);
        // std::cout << httpreqstr << std::endl;

        HttpResponse resp;
        resp._version = "HTTP/1.1";
        resp._code = 200;
        resp._desc = "OK";

        std::string filename = webroot + homepage; //"./wwwroot/index.html"
        bool res = Util::ReadFileContent(filename, &(resp._text));
        (void)res;

        std::string response_str = resp.Serialize();
        sock->Send(response_str);
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
