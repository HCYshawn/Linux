cmake_minimum_required(VERSION 3.18)

project(test
    LANGUAGES CXX
)

add_library(mystdio STATIC mystdio.cpp)
target_include_directories(mystdio PUBLIC .)

add_executable(main usercode.cpp)
target_link_libraries(main PRIVATE mystdio)