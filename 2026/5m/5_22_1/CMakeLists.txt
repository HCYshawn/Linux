# 1 设置最低版本
cmake_minimum_required(VERSION 3.18)

# 2 设置项目名称
project(LoggerDemo)

# 3 执行分支cmake
add_subdirectory(console_logger)
add_subdirectory(logger_interface)
add_subdirectory(app)
