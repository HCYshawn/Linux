#pragma once

#include "Common.hpp"
#include "Log.hpp"
#include "InetAddr.hpp"

using namespace LogModule;

const static int defaultsockfd = -1;
const static int backlog = 8;

class TcpServer : public NoCopy
{
public:
    TcpServer(uint16_t port) : _port(port), _listensockfd(defaultsockfd), _isrunning(false)
    {
    }
    void Init()
    {

        // 1. 创建套接字
        _listensockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (_listensockfd < 0)
        {
            LOG(LogLevel::FATAL) << "socket error";
            exit(SOCKET_ERR);
        }
        LOG(LogLevel::INFO) << "socket success" << _listensockfd;

        // 2. bind众所周知的端口号
        InetAddr local(_port);
        int n = bind(_listensockfd, local.NetAddrPtr(), local.NetAddrLen());
        if (n < 0)
        {
            LOG(LogLevel::FATAL) << "bind error";
            exit(BIND_ERR);
        }
        LOG(LogLevel::INFO) << "bind success: " << _listensockfd;

        // 3. 设置socket状态为listen
        n = listen(_listensockfd, backlog);
        if (n < 0)
        {
            LOG(LogLevel::FATAL) << "listen error";
            exit(LISTEN_ERR);
        }
        LOG(LogLevel::INFO) << "listen success: " << _listensockfd;
    }

    void Service(int sockfd, InetAddr &peer)
    {
        char buffer[1024];
        while (true)
        {
            ssize_t n = read(sockfd, buffer, sizeof(buffer) - 1);
            if (n > 0)
            {
                // 1. 先读取数据
                buffer[n] = 0;
                LOG(LogLevel::DEBUG) << peer.StringAddr() << " say# " << buffer;

                // 2. 写回数据
                std::string echo_string = "echo# ";
                echo_string += buffer;

                write(sockfd, echo_string.c_str(), echo_string.size());
            }
            else if (n == 0)
            {
                LOG(LogLevel::DEBUG) << peer.StringAddr() << "退出了...";
                close(sockfd);
                break;
            }
            else
            {
                LOG(LogLevel::DEBUG) << peer.StringAddr() << "异常...";
                close(sockfd);
                break;
            }
        }
    }

    void Run()
    {
        _isrunning = true;
        while (_isrunning)
        {
            // a. 获取链接
            struct sockaddr_in peer;
            socklen_t len = sizeof(sockaddr_in);
            int sockfd = accept(_listensockfd, CONV(peer), &len);
            if (sockfd < 0)
            {
                LOG(LogLevel::WARNING) << "accept error";
            }
            InetAddr addr(peer);
            LOG(LogLevel::INFO) << "accept success, peer addr : " << addr.StringAddr();

            // 测试
            Service(sockfd, addr);
        }
        _isrunning = false;
    }
    ~TcpServer()
    {
    }

private:
    uint16_t _port;
    int _listensockfd;

    bool _isrunning;
};