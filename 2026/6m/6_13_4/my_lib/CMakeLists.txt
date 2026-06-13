# 1 收集源代码
file(GLOB SRC_LISTS "src/*.cpp")

# 2 添加构建目标
add_library(MyMath SHARED ${SRC_LISTS})

# 3 设置库的使用要求
target_include_directories(MyMath PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)

# 4 设置库的默认输出路径
set_target_properties(MyMath PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  OUTPUT_NAME MyMath
  VERSION 1.2.3
  SOVERSION 20
  COMPILE_OPTIONS "-fPIC"
)

# 5 安装库文件
install(TARGETS MyMath)

# 6 安装头文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
)
