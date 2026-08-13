cmake_minimum_required(VERSION 3.16)

project(logsys
    VERSION 1.0.0
    DESCRIPTION "A header-only synchronous and asynchronous logging system"
    LANGUAGES CXX
)


option(LOGSYS_BUILD_EXAMPLES "Build logsys examples" ON)
option(LOGSYS_BUILD_BENCHMARKS "Build logsys benchmarks" ON)
option(LOGSYS_BUILD_TESTS "Build logsys tests" OFF)

find_package(Threads REQUIRED)

add_library(logsys INTERFACE)
add_library(logsys::logsys ALIAS logsys)

target_include_directories(logsys INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(logsys INTERFACE
    cxx_std_11
)

target_compile_definitions(logsys INTERFACE
    _GNU_SOURCE
)

target_link_libraries(logsys INTERFACE
    Threads::Threads
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(LOGSYS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(LOGSYS_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(LOGSYS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()