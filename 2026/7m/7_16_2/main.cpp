#include <iostream>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]) {
  (void)argc;
  (void)argv;
  for (int i = 0; env[i]; i++) {
    printf("env[%d]-> %s\n", i, env[i]);
  }
  return 0;
}
