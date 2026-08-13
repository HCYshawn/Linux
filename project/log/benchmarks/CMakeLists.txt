add_executable(bitlog_bench
    bench_logsys.cc
)

target_link_libraries(bitlog_bench PRIVATE
    bitlog
)