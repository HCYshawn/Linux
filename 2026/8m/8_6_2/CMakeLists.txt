cmake_minimum_required(VERSION 3.18)

project(fifo_worker_pool)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

 add_executable(dispatcher
    src/dispatcher.cpp
 )

target_include_directories(dispatcher PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

 add_executable(worker
    src/worker.cpp
)

target_include_directories(worker PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)