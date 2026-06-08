cmake_minimum_required(VERSION 3.18)

project(test)


message(STATUS "from top-level CMakeLists.txt")
# 打印 当前执行的源代码目录
message(STATUS "CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
# 打印 当前正在执行cmake的完整名称
message(STATUS "CMAKE_CURRENT_LIST_FILE:" ${CMAKE_CURRENT_LIST_FILE})
# 打印 当前正在执行cmake的全目录
message(STATUS "CMAKE_CURRENT_LIST_DIR:" ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(sub)