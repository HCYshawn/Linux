cmake_minimum_required(VERSION 3.18)

project(TestMyMath
  LANGUAGES CXX
)

# 1 开启测试
include(CTest)

# 2 添加测试执行文件
add_executable(main main.cpp)

# 3 查找MyMath库
find_package(MyMath CONFIG REQUIRED)

# 4 链接MyMath库
target_link_libraries(main PRIVATE MyMath)

# 5 添加测试case 到CTest
add_test(
  NAME TestMyMath
  COMMAND main
)


