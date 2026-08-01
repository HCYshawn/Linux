cmake_minimum_required(VERSION 3.18)

project(test
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(process_pool
    main.cpp
)

target_include_directories(process_pool PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)