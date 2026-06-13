cmake_minimum_required(VERSION 3.18)

project(JsoncppDemo
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

# 查找jsoncpp使用config模式
find_package(jsoncpp CONFIG REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE JsonCpp::JsonCpp)
