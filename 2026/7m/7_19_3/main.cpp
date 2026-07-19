#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t id = fork();

  if (id == 0) {
    std::cout << "child running..." << std::endl;
    sleep(2);
    return 10;
  } else if (id > 0) {
    int status = 0;
    pid_t ret = wait(&status);

    if (ret > 0) {
      if (WIFEXITED(status)) {
        std::cout << "child normal exit" << std::endl;
        std::cout << "exit code: " << WEXITSTATUS(status) << std::endl;
      } else {
        std::cout << "child abnormal exit" << std::endl;
      }
    }
  }
  return 0;
}
