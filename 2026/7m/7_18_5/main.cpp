#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("running...\n");
  execl("/usr/bin/ls", "ls", "-l", "-a", NULL);
  printf("done.\n");
  return 0;
}
