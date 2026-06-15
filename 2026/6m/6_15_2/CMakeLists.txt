cmake_minimum_required(VERSION 3.18)

project(test)

# 非
if(NOT "OFF")
  message("1: true")
else()
  message("1: false")
endif()

# 与
if("ON" AND  "OFF")
  message("2: true")
else()
  message("2: false")
endif()

# 或
if("ON" OR  "OFF")
  message("3: true")
else()
  message("3: false")
endif()
