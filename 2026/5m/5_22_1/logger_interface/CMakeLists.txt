add_library(LoggerInterface STATIC logger.cpp)
target_include_directories(LoggerInterface
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(LoggerInterface PRIVATE ConsoleLogger)
