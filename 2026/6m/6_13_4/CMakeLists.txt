cmake_minimum_required(VERSION 3.18)

project(InstallMyMath
    LANGUAGES CXX
)

add_subdirectory(my_lib)

add_subdirectory(app)

include(CPack)

set(CPACK_PACKAGE_NAME "MyApp")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_GENERATIOR "TGZ")
