cmake_minimum_required(VERSION 3.18)

project(test)

set(i 1)

while(i LESS_EQUAL 5)
    message(STATUS "i = ${i}")
    math(EXPR i "${i} +1")

endwhile()
