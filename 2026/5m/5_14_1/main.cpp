#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("parent coming,pid: %d \n", getpid());
  pid_t id = fork();
  if (id < 0) {
    perror("fork");
    return 1;
  } else if (id == 0) {
    while (1) {
      sleep(1);
      printf("I am cpid! my pid: %d, my parent id :%d\n", getpid(), getppid());
    }
  } else {
    while (1) {
      sleep(1);
      printf("I am ppid! my pppid: %d, my parent id :%d\n", getpid(),
             getppid());
    }
  }
  return 0;
}
