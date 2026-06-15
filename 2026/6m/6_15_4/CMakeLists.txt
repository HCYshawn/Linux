cmake_minimum_required(VERSION 3.18)

project(test)

# file 文件存在性 检测
if(EXISTS ${CMAKE_CURRENT_LIST_FILE})
    message("1: true")
else()
    message("1: false")
endif()


# file 文件存在性 检测
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
    message("2: true")
else()
    message("2: false")
endif()

# file 路径存在性 检测
if(EXISTS "")
    message("3: true")
else()
    message("3: false")
endif()

# file 路径存在性 检测
if(EXISTS "../CMakeLists.txt")
    message("4: true")
else()
    message("4: false")
endif()