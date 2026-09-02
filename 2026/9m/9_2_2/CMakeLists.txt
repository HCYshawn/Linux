cmake_minimum_required(VERSION 3.16)

project(Sem)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE pthread)
target_link_directories(main PRIVATE RingQueue.hpp)
target_link_directories(main PRIVATE Sem.hpp)
