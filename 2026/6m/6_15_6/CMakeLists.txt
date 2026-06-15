cmake_minimum_required(VERSION 3.18)

project(test)

# 版本号比较
set(VERSION "1.2.3")
if(VERSION VERSION_LESS "1.3.0")
    message("1: true")
else()
    message("1: false")
endif()