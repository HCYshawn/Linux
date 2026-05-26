cmake_minimum_required(VERSION 3.18)

project(TestProp
  LANGUAGES CXX
)

add_subdirectory(src)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE add)
