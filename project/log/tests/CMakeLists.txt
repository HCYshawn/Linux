add_executable(logsys_logger_builder_test
    logger_builder_test.cc
)

target_link_libraries(logsys_logger_builder_test PRIVATE
    logsys::logsys
)

add_test(NAME logsys_logger_builder_test COMMAND logsys_logger_builder_test)