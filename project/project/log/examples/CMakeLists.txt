add_executable(bitlog_example
    test.cc
)

target_link_libraries(bitlog_example PRIVATE
    bitlog
)