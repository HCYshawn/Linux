#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t id = fork();
  if (id == 0) {
    int cnt = 3;
    while (cnt) {
      printf("我是子进程,pid : %d, ppid: %d\n", getpid(), getppid());
      sleep(1);
      cnt--;
    }
    exit(10);
  }

  // 父进程
  int status = 0;
  pid_t rid = waitpid(id, &status, 0);
  if (rid > 0) {
    printf("wait success, rid: %d,exit code: %d\n", rid, (status >> 8) & 0xFF);
  }
  return 0;
}
