cmake_minimum_required(VERSION 3.18)

project(Tcpserver
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tcpserver TcpServer.cpp)
target_link_libraries(tcpserver PRIVATE pthread)

# add_executable(udpclient UdpClient.cpp)
# target_link_libraries(udpclient PRIVATE pthread)