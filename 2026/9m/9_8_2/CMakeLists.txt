cmake_minimum_required(VERSION 3.18)

project(Udpserver
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(udpserver UdpServer.cpp)

add_executable(udpclient UdpClient.cpp)
target_link_libraries(udpclient PRIVATE pthread)