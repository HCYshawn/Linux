# 1 收集源代码
file(GLOB SRC_LISTS "src/*.cpp")

# 2 添加构建目标
add_library(MyMath SHARED ${SRC_LISTS})

# 3 设置库的使用要求
target_include_directories(MyMath
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include 
)

# 4 设置库的默认输出路径
set_target_properties(MyMath PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# 5 添加 -fPIC 编译选项
target_compile_options(MyMath PRIVATE "-fPIC")
