message(STATUS "from sub/sub.cmake")
# 打印 当前正在执行的源代码目录--- 即CMakeLists.txt所在目录
message(STATUS "CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
# 打印 当前正在执行的 cmake 脚本的完整名称
message(STATUS "CMAKE_CURRENT_LIST_FILE:" ${CMAKE_CURRENT_LIST_FILE})
# 打印 当前正在执行的cmake脚本的全目录
message(STATUS "CMAKE_CURRENT_LIST_DIR:" ${CMAKE_CURRENT_LIST_DIR})
