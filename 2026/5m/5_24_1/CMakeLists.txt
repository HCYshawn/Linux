cmake_minimum_required(VERSION 3.18)

project(CurlDemo
  VERSION 1.0.0
  LANGUAGES CXX
)

# 查找curl库
find_package(CURL REQUIRED CONFIG)

# 创建可执行文件
add_executable(main main.cpp)

#使用导入目标形式链接curl
target_link_libraries(main PRIVATE CURL::libcurl_static)

