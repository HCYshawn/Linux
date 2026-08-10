add_executable(bitlog_internal_test
    internal_test.cc
)

target_link_libraries(bitlog_internal_test PRIVATE
    bitlog
)

add_test(NAME bitlog_internal_test COMMAND bitlog_internal_test)