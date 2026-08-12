#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void handler(int signum) {
  std::cout << "child get signal: " << signum << std::endl;
}

int main() {
  pid_t id = fork();

  if (id == 0) {
    signal(SIGUSR1, handler);

    while (true) {
      std::cout << "child pid: " << getpid() << ", waiting..." << std::endl;
      sleep(1);
    }
  }

  sleep(3);

  kill(id, SIGUSR1);

  waitpid(id, nullptr, 0);
  return 0;
}
