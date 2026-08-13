add_executable(bitlog_logger_builder_test
    logger_builder_test.cc
)

target_link_libraries(bitlog_logger_builder_test PRIVATE
    bitlog
)

add_test(NAME bitlog_logger_builder_test COMMAND bitlog_logger_builder_test)