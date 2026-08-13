add_executable(bitlog_example
    basic_example.cc
)

target_link_libraries(bitlog_example PRIVATE
    bitlog
)