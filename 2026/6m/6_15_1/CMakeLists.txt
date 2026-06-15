cmake_minimum_required(VERSION 3.18)

project(IFBasicExprDemo)

# 1 命令常量真
if("ON")
  message("1: true")
else()
  message("1: false")
endif()


# 2 命令常量假
if("OFF")
  message("2: true")
else()
  message("2: false")
endif()


# 3 数字真
if("1")
  message("3: true")
else()
  message("3: false")
endif()

# 4 数字假
if("0")
  message("4: true")
else()
  message("4: false")
endif()

# 5 不能转换为数字的字符串
if("123A")
  message("5: true")
else()
  message("5: false")
endif()

# 6 变量真
set(OS "linux")
if(OS)
  message("6: true")
else()
  message("6: false")
endif()

# 7 变量假
set(OS "OFF")
if(OS)
  message("7: true")
else()
  message("7: false")
endif()

# 8 字符串字面量--普通
if("abc")
  message("8: true")
else()
  message("8: false")
endif()

# 9 字符串字面量--常量
if("on")
  message("9: true")
else()
  message("9: false")
endif()



