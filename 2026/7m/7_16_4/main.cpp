#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]) {
  (void)argc;
  (void)argv;
  (void)env;

  char *who = getenv("USER");
  if (who == nullptr)
    return 0;
  if (strcmp(who, "ubuntu") == 0) {
    std::cout << "This is true\n";
  } else {
    std::cout << "This is false\n";
  }
  return 0;
}
