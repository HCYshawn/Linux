#pragma once
#include <iostream>
#include <string>

class ConsoleLogger {
public:
  static void log(const std::string &msg) {
    std::cout << " [LOG] " << msg << std::endl;
  }
};
