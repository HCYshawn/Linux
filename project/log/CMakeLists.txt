cmake_minimum_required(VERSION 3.16)

project(bitlog LANGUAGES CXX)

option(BITLOG_BUILD_EXAMPLES "Build bitlog examples" ON)
option(BITLOG_BUILD_BENCHMARKS "Build bitlog benchmarks" ON)
option(BITLOG_BUILD_TESTS "Build bitlog tests" OFF)

find_package(Threads REQUIRED)

add_library(bitlog INTERFACE)

target_include_directories(bitlog INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(bitlog INTERFACE
    cxx_std_11
)

target_compile_definitions(bitlog INTERFACE
    _GNU_SOURCE
)

target_link_libraries(bitlog INTERFACE
    Threads::Threads
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(BITLOG_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BITLOG_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(BITLOG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()