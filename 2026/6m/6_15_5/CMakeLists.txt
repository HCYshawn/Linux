cmake_minimum_required(VERSION 3.18)

project(test)

# 实数比较
if("20" LESS "30")
    message("1: true")
else()
    message("1: false")
endif()

# 字符串比较
if("abc" STRLESS "abd")
    message("2: true")
else()
    message("2: false")
endif()