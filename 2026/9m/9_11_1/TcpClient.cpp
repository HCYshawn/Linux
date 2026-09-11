#include <iostream>
#include "Common.hpp"
#include "InetAddr.hpp"

void Usage(std::string proc)
{
    std::cerr << "Usage: " << proc << " serve_ip server_port" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }
    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);

    // 1. 创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "socket error" << std::endl;
        exit(SOCKET_ERR);
    }

    // 2. 直接向目标服务器发起连接请求
    InetAddr serveraddr(serverip, serverport);
    int n = connect(sockfd, serveraddr.NetAddrPtr(), serveraddr.NetAddrLen());

    // 3. echo client
    while (true)
    {
        std::string line;
        std::cout << "Please ENter@ ";
        std::getline(std::cin, line);

        write(sockfd, line.c_str(), line.size());

        char buffer[1024];
        ssize_t size = read(sockfd, buffer, sizeof(buffer) - 1);
        if (size > 0)
        {
            buffer[size] = 0;
            std::cout << "Server echo# " << buffer << std::endl;
        }
    }
    close(sockfd);
    return 0;
}