#pragma once

#include "Common.hpp"
#include "Log.hpp"
#include "InetAddr.hpp"
#include "ThreadPool.hpp"
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

using namespace LogModule;
using namespace ThreadPoolModule;

// using task_t = std::function<void()>;
using func_t = std::function<std::string(const std::string &, InetAddr &peer)>;

const static int defaultsockfd = -1;
const static int backlog = 8;

class TcpServer : public NoCopy
{
public:
    TcpServer(uint16_t port, func_t func) : _port(port), _listensockfd(defaultsockfd), _isrunning(false), _func(func)
    {
    }
    void Init()
    {
        signal(SIGCHLD, SIG_IGN);
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

    class ThreadData
    {
    public:
        ThreadData(int fd, InetAddr &ar, TcpServer *s)
            : sockfd(fd),
              addr(ar),
              tsvr(s)
        {
        }

    public:
        int sockfd;
        InetAddr addr;
        TcpServer *tsvr;
    };

    // 长服务，多进程多线程合适
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
                LOG(LogLevel::DEBUG) << peer.StringAddr() << " # " << buffer;

                std::string echo_string = _func(buffer, peer);

                // 2. 写回数据
                // std::string echo_string = "echo# ";
                // echo_string += buffer;

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

    static void *Routine(void *args)
    {
        pthread_detach(pthread_self());
        ThreadData *td = static_cast<ThreadData *>(args);
        td->tsvr->Service(td->sockfd, td->addr);
        delete td;
        return nullptr;
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

            // 多线程
            ThreadData *td = new ThreadData(sockfd, addr, this);
            pthread_t tid;
            pthread_create(&tid, nullptr, Routine, td);

            // // 测试
            // Service(sockfd, addr);

            // 多进程
            //  pid_t id = fork();
            //  if (id < 0)
            //  {
            //      LOG(LogLevel::FATAL) << "fork error";
            //      exit(FORK_ERR);
            //  }
            //  else if (id == 0)
            //  {
            //      // 子进程
            //      close(_listensockfd);
            //      // 子进程创建孙进程，子进程退出
            //      if (fork() > 0)
            //      {
            //          exit(OK);
            //      }
            //      // 交由孙进程继续执行，同时由1号进程接管
            //      Service(sockfd, addr);
            //      exit(OK);
            //  }
            //  else
            //  {
            //      // 父进程
            //      close(sockfd);

            //     pid_t rid = waitpid(id, nullptr, 0);
            //     (void)rid;
            // }

            // 多线程
            // ThreadData *td = new ThreadData(sockfd, addr, this);
            // pthread_t tid;
            // pthread_create(&tid, nullptr, Routine, td);

            // 线程池，一般适合短服务
            // ThreadPool<task_t>::GetInstance()->Enqueue([this, sockfd, &addr]()
            //                                            { this->Service(sockfd, addr); });
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

    func_t _func;
};