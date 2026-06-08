#include "math/calculator.h"
#include "utils/string_utils.h"   // 内部使用 trim，但不想暴露给 math 的使用者
#include <string>
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }