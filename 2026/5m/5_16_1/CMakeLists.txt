# 1 设置最低 cmake 版本
cmake_minimum_required(VERSION 3.18)

# 2 设置项目名称
project(InstallHello
  VERSION 1.2.3
  LANGUAGES C CXX
)

# 3 添加构建目标
add_executable(hello main.cpp)

# 4 安装到本地
include(GNUInstallDirs)
install(TARGETS hello)

# printf
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

# 打印版本信息
message(STATUS "PROJECT_VERSION : ${PROJECT_VERSION}")
message(STATUS "PROJECT_VERSION_MAJOR: ${PROJECT_VERISON_MAJOR}")
