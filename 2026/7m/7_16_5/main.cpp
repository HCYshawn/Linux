#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[], char *env[]) {
  (void)argc;
  (void)argv;
  for (int i = 0; environ[i]; i++) {
    printf("environ[%d]-> %s\n", i, environ[i]);
  }
  return 0;
}
