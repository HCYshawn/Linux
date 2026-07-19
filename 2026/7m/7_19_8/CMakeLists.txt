cmake_minimum_required(VERSION 3.10)
project(EnvTest LANGUAGES CXX)   # 显式指定 C++

set(CMAKE_CXX_STANDARD 11)       # 或 14、17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(other other.cpp)
add_executable(main  main.cpp)