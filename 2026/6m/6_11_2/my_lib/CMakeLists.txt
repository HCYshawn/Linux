# 1 收集源代码
file(GLOB SRC_LISTS "src/*.cpp")

# 2 添加构建目标
add_library(MyMath SHARED ${SRC_LISTS})

# 3 设置库的使用要求，也就是下游消费者必须包含的头文件搜索路径
target_include_directories(MyMath INTERFACE
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEIR}>"
)

# 4 设置库的默认输出路径
set_target_properties(MyMath PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  OUTPUT_NAME MyMath
  VERSION 1.2.3
  SOVERSION 20
  COMPILE_OPTIONS "-fPIC"
)

# 5 安装静态库
include(GNUInstallDirs)
install(TARGETS MyMath
  EXPORT MyMathTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# 6 安装头文件
install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/math
  FILES_MATCHING PATTERN "*.h"
)

# 7 安装导出目标集合 到 构建树
export(EXPORT MyMathTargets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/MyMathTargets.cmake
)

# 8 安装导出目标集合 到 安装树
install(EXPORT MyMathTargets
  FILE MyMathTargets.cmake
  NAMESPACE MyMath::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyMath
)

# 9 生成find_package需要的 配置文件
include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/MyMathConfig.cmake
  INSTALL_DESTINATION "lib/cmake/MyMath"
)
# 10 安装配置文件到cmake标准的安装路径
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/MyMathConfig.cmake
  DESTINATION "lib/cmake/MyMath"
)
