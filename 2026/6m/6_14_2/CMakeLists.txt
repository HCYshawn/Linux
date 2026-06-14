cmake_minimum_required(VERSION 3.18)

project(FunctionScopDemo)

set(SCOP "Directory Scop")

function(print_var)
  # 1 获取父级目录变量
  message("1 func: ${SCOP}")

  # 2 修改变量
  set(SCOP "Function Scop" PARENT_SCOPE)
  message("2 func: ${SCOP}")
endfunction(print_var)

print_var()
message("3 main: ${SCOP}")

