cmake_minimum_required(VERSION 3.16)

project(Thread)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC pthread)
target_link_directories(main PUBLIC Thread.hpp)