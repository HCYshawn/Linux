add_executable(bitlog_bench
    bench.cc
)

target_link_libraries(bitlog_bench PRIVATE
    bitlog
)