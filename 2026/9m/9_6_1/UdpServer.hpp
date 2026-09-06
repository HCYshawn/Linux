#pragma once

#include <iostream>
#include <string>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"

using namespace LogModule;

const int defaultfd = -1;

class UdpServer
{
public:
    UdpServer(const std::string &ip, uint16_t port)
        : _sockfd(defaultfd),
          _ip(ip),
          _port(port)
    {
    }
    void Init()
    {
        // 1. 创建套接字
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            LOG(LogLevel::FATAL) << "soucket error!";
        }
        LOG(LogLevel::INFO) << "socket success, sockfd: " << _sockfd;

        // 2. 绑定socket信息，ip、端口
        struct sockaddr_in local;
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET;

        //本地格式转为网络序列，即大端
        local.sin_port = htons(_port);

    }
    void Start()
    {
    }
    ~UdpServer()
    {
    }

private:
    int _sockfd;
    uint16_t _port;
    std::string _ip;
};