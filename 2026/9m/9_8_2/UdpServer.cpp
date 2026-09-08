#include <iostream>
#include <memory>
#include "UdpServer.hpp" //网络通信功能
#include "Route.hpp"

std::string defaluthandler(const std::string &message)
{
    std::string hello = "hello, ";
    hello += message;
    return hello;
}

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

    // 2. 提供网络服务器对象实现网络通信
    std::unique_ptr<UdpServer> usvr = std::make_unique<UdpServer>(port, [&r](int sockfd, const std::string &message, InetAddr &peer)
                                                                  { r.MessageRoute(sockfd, message, peer); });

    usvr->Init();
    usvr->Start();

    return 0;
}