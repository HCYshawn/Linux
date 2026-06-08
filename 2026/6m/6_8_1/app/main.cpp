#include "math/calculator.h"
#include <iostream>
int main() {
    std::cout << "add(2,3) = " << add(2,3) << std::endl;
    std::cout << "sub(5,2) = " << sub(5,2) << std::endl;
    // 注意：这里故意不包含 utils/string_utils.h，看看能不能编译通过
    return 0;
}