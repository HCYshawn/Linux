#include <iostream>
#include <vector>

int main() {
  std::vector<int> a = {1, 2, 3};
  a.push_back(1);
  for (int i = 0; i < 4; i++) {
    std::cout << a[i] << " " << std::endl;
  }
  return 0;
}
