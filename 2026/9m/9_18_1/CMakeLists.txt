cmake_minimum_required(VERSION 3.18)

project(mysqlconnecttest)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE mysqlcppconn)