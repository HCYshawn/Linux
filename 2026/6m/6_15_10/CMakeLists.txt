cmake_minimum_required(VERSION 3.18)

project(test)

function(print_args first scond)
    message("ARGC = ${ARGC}") # 实参总个数
    message("ARGV = ${ARGV}")# 实参列表
    message("ARGV0 = ${ARGV0}")# 第一个
    message("ARGV1 = ${ARGV1}")# 第二个
    message("ARGV2 = ${ARGV2}")# 第三个
    message("ARGN = ${ARGN}")# 剩余列表
endfunction()

print_args(A B C D E)

function(sum A B)
    math(EXPR RESULT "${A} + ${B}")
    set(LOCAL_SUM ${RESULT})# 局部变量
    set(OUTPUT_SUM ${RESULT} PARENT_SCOPE)# 父级作用域变量
    set(CACHE_SUM ${RESULT} CACHE STRING "sum")# 缓存变量
endfunction(sum A B)

sum(3 5)
message(STATUS "LOCAL_SUM = ${LOCAL_SUM}")
message(STATUS "OUTPUT_SUM = ${OUTPUT_SUM}")
message(STATUS "CACHE_SUM = $CACHE{CACHE_SUM}")