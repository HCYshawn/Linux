cmake_minimum_required(VERSION 3.18)

project(test
    LANGUAGES CXX
)

add_executable(sever server.cpp)
add_executable(client client.cpp)