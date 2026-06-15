cmake_minimum_required(VERSION 3.18)

project(test)

# COMMAND 检测
if(COMMAND project)
    message("1: true")
else()
    message("1: false")
endif()

# target 检测
add_library(MyMath INTERFACE IMPORTED)
if(TARGET myMath)
    message("2: true")
else()
    message("2: false")
endif()

# DEFINED 普通变量是否定义 检测
set(NAME "linux")
if(DEFINED NAME)
    message("3: true")
else()
    message("3: false")
endif()

# DEFINED 缓存变量是否定义 检测
#set(AGE "18" CACHE STRING "abc")
if(DEFINED AGE)
    message("4: true")
else()
    message("4: false")
endif()

# DEFINED 环境变量是否定义 检测
if(DEFINED ENV{EMAIL})
    message("3: true")
else()
    message("3: false")
endif()