#pragma once

#include <iostream>
#include <string>
#include <memory>
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

    ~Response()
    {
    }

private:
    int _result; // 运算结果
    int _code;   // 运算结果退出码
};

class Protocol
{
public:
    Protocol()
    {
    }

    void GetRequest(std::shared_ptr<Socket> &sock, InetAddr &client)
    {
    }

    ~Protocol()
    {
    }

private:
    Request _req;
    Response _resp;
};