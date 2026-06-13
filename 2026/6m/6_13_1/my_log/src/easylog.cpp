#include "easylog.h"
#include <iostream>

void print_info(const std::string &msg) {
  std::cout << "[INFO] " << msg << std::endl;
}

void print_error(const std::string &msg) {
  std::cerr << "[ERROR] " << msg << std::endl;
}
