cmake_minimum_required(VERSION 3.16)

project(ThreadPool
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)
target_link_directories(main PRIVATE Log.hpp)
target_link_directories(main PRIVATE Mutex.hpp)