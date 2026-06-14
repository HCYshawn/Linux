cmake_minimum_required(VERSION 3.18)

project(DirectScopeDemo)

set(SCOP "Parent Scop")

add_subdirectory(sub)

message("main: ${SCOP}")
