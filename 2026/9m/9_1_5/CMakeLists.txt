cmake_minimum_required(VERSION 3.16)

project(Cond)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE pthread)
target_link_directories(main PRIVATE BlockQueue.hpp)
target_link_directories(main PRIVATE Task.hpp)
target_link_directories(main PRIVATE Cond.hpp)
target_link_directories(main PRIVATE Mutex.hpp)
