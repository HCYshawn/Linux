#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef void (*func_t)();

#define NUM 5

func_t handlers[NUM + 1];

void DownLoad() { printf("我是一个下载任务...\n"); }

void Flush() { printf("我是一个刷新任务...\n"); }

void Log() { printf("我是一个记录日志任务...\n"); }

void registerHandler(func_t h[], func_t f) {
  int i = 0;
  for (; i < NUM; i++) {
    if (h[i] == nullptr) {
      break;
    }
  }
  if (i == NUM) {
    return;
  }
  h[i] = f;
  h[i + 1] = nullptr;
}

int main() {
  registerHandler(handlers, DownLoad);
  registerHandler(handlers, Flush);
  registerHandler(handlers, Log);

  pid_t id = fork();

  if (id < 0) {
    perror("fork");
    return 1;
  } else if (id == 0) {
    int cnt = 3;
    while (cnt > 0) {
      sleep(3);
      printf("我是子进程, pid: %d, ppid: %d\n", getpid(), getppid());

      sleep(1);
      cnt--;
    }
    exit(10);
  } else {
    while (true) {
      int status = 0;
      pid_t rid = waitpid(id, &status, WNOHANG);

      if (rid > 0) {
        if (WIFEXITED(status)) {
          printf("wait success, rid: %d, child mormal exit, exit code: %d\n",
                 rid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
          printf("wait success, rid: %d, child killed by signal: %d\n", rid,
                 WTERMSIG(status));
        } else {
          printf("wait success, rid: %d, child exit status unknown\n", rid);
        }
        break;
      } else if (rid == 0) {
        for (int i = 0; handlers[i] != nullptr; i++) {
          handlers[i]();
        }
        printf("本轮调用结束, 子进程没有退出\n\n");
        sleep(1);
      } else {
        perror("waitpid");
        break;
      }
    }
  }

  return 0;
}
