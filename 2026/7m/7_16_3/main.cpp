#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]) {
  (void)argc;
  (void)argv;
  (void)env;

  char *value = getenv("PATH");
  if (value == nullptr)
    return 1;
  printf("PATH-> %s\n", value);
  return 0;
}
