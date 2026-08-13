add_executable(logsys_example
    basic_example.cc
)

target_link_libraries(logsys_example PRIVATE
    logsys::logsys
)