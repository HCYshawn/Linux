#include "math/math.h"
#include <cassert>
#include <iostream>

int main() {
  assert(add(2, 3) == 5);

  assert(sub(2, 3) == -1);

  std::cout << "test OK" << std::endl;
  return 0;
}
