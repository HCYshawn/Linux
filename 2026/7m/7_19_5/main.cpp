#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  printf("running...\n");
  if (fork() == 0) {
    sleep(1);
    execl("/usr/bin/ls", "ls", "-l", "-a", NULL);
    sleep(1);
    exit(1);
  }
  waitpid(-1, NULL, 0);
  printf("done.\n");
  return 0;
}
