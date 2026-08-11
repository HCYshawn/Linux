#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void handlerSig(int sig)
{
  std::cout << "获得了一个信号: " << sig << std::endl;
}

int main()
{
  signal(SIGINT, handlerSig);
  int cnt = 0;
  while (true)
  {
    std::cout << "cnt: " << cnt++ << ", pid: " << getpid() << std::endl;
    sleep(1);
  }
  return 0;
}
