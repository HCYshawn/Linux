#include <iostream>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s [-a|-b|-c]\n", argv[0]);
    return 1;
  }
  const char *arg = argv[1];
  if (strcmp(arg, "-a") == 0)
    printf("这是功能1\n");
  else if (strcmp(arg, "-b") == 0)
    printf("这是功能2\n");
  else if (strcmp(arg, "-c") == 0)
    printf("这是功能3\n");
  else
    printf("Usage: %s [-a|-b|-c]\n", argv[0]);

  return 0;
}
