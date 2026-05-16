# 1 设置最低版本
cmake_minimum_required(VERSION 3.18)

# 2 设置项目名称
project(installHello)

# 3 添加构建目标
add_executable(hello main.cpp)

# 4 安装到本地
include(GNUInstallDirs)
install(TARGETS hello)

# print
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

# print VERSION
message(STATUS "PROJECT_VERSION:" ${PROJECT_VERSION})
message(STATUS "PROJECT_VERSION_MAJOR:" ${PROJECT_VERSION_MAJOR})
message(STATUS "PROJECT_VERSION_MINOR:" ${PROJECT_VERSION_MINOR})
message(STATUS "PROJECT_VERSION_PATCH:" ${PROJECT_VERSION_PATCH})

# 打印 默认安装路径
message(STATUS "PROJECT_VERSION_PATCH:" ${CMAKE_INSTALL_PREFIX})

