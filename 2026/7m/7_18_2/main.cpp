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
    int cnt = 5;
    while (cnt) {
      printf("我是子进程,pid : %d, ppid: %d\n", getpid(), getppid());
      sleep(1);
      cnt--;
    }
    exit(0);
  }

  sleep(10);
  // 父进程
  pid_t rid = waitpid(id, NULL, 0);
  if (rid > 0) {
    printf("wait success, rid: %d\n", rid);
  }
  return 0;
}
