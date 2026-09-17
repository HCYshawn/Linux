cmake_minimum_required(VERSION 3.16)

project(test
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE jsoncpp)

add_executable(client TcpClient.cpp)
target_link_libraries(client PRIVATE jsoncpp)