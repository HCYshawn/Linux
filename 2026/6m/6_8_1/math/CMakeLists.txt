add_library(math STATIC src/calculator.cpp)
target_include_directories(math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(math PRIVATE utils)