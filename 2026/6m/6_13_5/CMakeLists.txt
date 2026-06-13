cmake_minimum_required(VERSION 3.18)

project(ProtoExample
  LANGUAGES CXX 
)

# 设置C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 1 查找Protobuf 库 要求版本 >= 3.0
find_package(Protobuf 3.0 REQUIRED)

# 2 收集proto 项目描述文件
file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto)

# 3 创建protoc 的生成文件目录
set(PB_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/pb)
file(MAKE_DIRECTORY ${PB_OUT_DIR})

# 4 初始化生成的源代码文件集合,
set(GEN_SRCS "")  # *.pb.cc
set(GEN_HEADS "") #*.pb.h

# 5 为每一个proto文件生成对应的.cc 和.h 文件
foreach(PROTO ${PROTO_FILES})
  # 5.1 获取不带扩展名的文件名字
  get_filename_component(BASE_NAME ${PROTO} NAME_WE)

  # 5.2 添加生成的C++ 文件到 源代码集合
  list(APPEND GEN_SRCS "${PB_OUT_DIR}/${BASE_NAME}.pb.cc")
  list(APPEND GEN_HEADS "${PB_OUT_DIR}/${BASE_NAME}.pb.h")

  # 5.3 为每一个proto文件生成C++文件
  add_custom_command(
    OUTPUT "${PB_OUT_DIR}/${BASE_NAME}.pb.cc" "${PB_OUT_DIR}/${BASE_NAME}.pb.h"
    COMMAND protoc
    ARGS --cpp_out=${PB_OUT_DIR}
        -I ${CMAKE_CURRENT_SOURCE_DIR}/proto
        ${PROTO}
    DEPENDS ${PROTO}
    COMMENT "从*.proto 生成对应的C++代码"
    VERBATIM
  )

endforeach()

# 6 添加出发生成pb文件的目标
add_custom_target(generate_protobuf DEPENDS ${GEN_SRCS} ${GEN_HEADS})

# 7 把proto 生成的C++ 文件编译成我们的静态库
add_library(MyProto STATIC ${GEN_SRCS})
add_dependencies(MyProto generate_protobuf)
target_include_directories(MyProto INTERFACE
  ${PB_OUT_DIR}
)
target_link_libraries(MyProto PUBLIC protobuf::libprotobuf)

# 8 添加可执行程序
add_executable(main main.cpp)

# 9 添加依赖关系
target_link_libraries(main PRIVATE MyProto)


