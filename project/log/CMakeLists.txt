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

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

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



install(TARGETS logsys
    EXPORT logsysTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT logsysTargets
    FILE logsysTargets.cmake
    NAMESPACE logsys::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/logsys
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/logsysConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/logsysConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/logsys
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/logsysConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/logsysConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/logsysConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/logsys
)