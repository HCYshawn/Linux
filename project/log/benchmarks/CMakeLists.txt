add_executable(logsys_bench
    bench_logsys.cc
)

target_link_libraries(logsys_bench PRIVATE
    logsys::logsys
)