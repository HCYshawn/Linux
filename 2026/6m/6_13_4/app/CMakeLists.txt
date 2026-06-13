# 1 搜集文件列表
file(GLOB SRC_LISTS "*.cpp")

# 2 添加构建目标
add_executable(main ${SRC_LISTS})

# 3 添加依赖库列表
target_link_libraries(main PRIVATE MyMath)

# 4 设置输出路径
set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  INSTALL_RPATH "$ORIGIN/../lib"
)

# 5 打印动态库的输出路径
add_custom_command(
  TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo
  "$<PATH:RELATIVE_PATH,$<TARGET_FILE:MyMath>,${CMAKE_CURRENT_BINARY_DIR}>"
  COMMENT "获取动态库的输出路径"
)

# 6 安装main
install (TARGETS main)
