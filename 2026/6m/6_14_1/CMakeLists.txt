cmake_minimum_required(VERSION 3.18)

project(MessageDemo)

message("begin CMakeLists.txt")
message(STATUS "begin CMakeLists.txt")

message(STATUS "1" "2" "3")
message(STATUS "123")

#message(WARNING "this is a WARNING")

#message(SEND_ERROR "this is a SEND_ERROR")

#message(FATAL_ERROR "this is a FATAL_ERROR")

message(STATUS "end CMakeLists.txt")