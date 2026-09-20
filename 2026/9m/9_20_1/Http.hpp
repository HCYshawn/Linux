#pragma once

#include "Socket.hpp"
#include "TcpServer.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

using namespace SocketModule;

const std::string gspace = " ";
const std::string glinespace = "\r\n";
const std::string glinesep = ": ";

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

    bool Deserialize(std::string &reqstr)
    {
        return true;
    }

    ~HttpRequest()
    {
    }

private:
    std::string _method;
    std::string _url;
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
        sock->Recv(&httpreqstr);
        std::cout << httpreqstr << std::endl;

        HttpResponse resp;
        resp._version = "HTTP/1.1";
        resp._code = 200;
        resp._desc = "OK";

        resp._text = "<!DOCTYPE html>\
                     < html >\
                     <body>\
                         Hello,World !</ body> < / html > ";

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
