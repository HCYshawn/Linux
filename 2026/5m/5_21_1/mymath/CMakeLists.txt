add_library(mymath STATIC
  src/add.cpp
  src/sub.cpp
)

target_include_directories(mymath
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(mymath PRIVATE BUILDING_MYMATH)

