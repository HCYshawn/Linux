cmake_minimum_required(VERSION 3.18)

project(testmymath)

add_executable(main main.cpp)

find_package(MyMath CONFIG REQUIRED)

target_link_libraries(main PRIVATE MyMath::MyMath)