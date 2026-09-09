#include <iostream>
#include <memory>
#include "UdpServer.hpp" //网络通信功能
#include "Route.hpp"
#include "ThreadPool.hpp"

using namespace ThreadPoolModule;

std::string defaluthandler(const std::string &message)
{
    std::string hello = "hello, ";
    hello += message;
    return hello;
}

using task_t = std::function<void()>;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << "port" << std::endl;
    }
    // std::string ip = argv[1];
    uint16_t port = std::stoi(argv[1]);

    Enable_Console_Log_Strategy();

    // 1. 路由服务
    Route r;

    // 2. 线程池
    auto tp = ThreadPool<task_t>::GetInstance();

    // 3. 提供网络服务器对象实现网络通信
    std::unique_ptr<UdpServer> usvr = std::make_unique<UdpServer>(port, [&r, &tp](int sockfd, const std::string &message, InetAddr &peer)
                                                                  { task_t t = std::bind(&Route::MessageRoute, &r, sockfd, message, peer); });

    // std::unique_ptr<UdpServer> usvr = std::make_unique<UdpServer>(port, [&r](int sockfd, const std::string &message, InetAddr &peer){ r.MessageRoute(sockfd, message, peer); });

    usvr->Init();
    usvr->Start();

    return 0;
}