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

class HttpRequest
{
public:
    HttpRequest()
    {
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
