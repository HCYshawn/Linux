#include <iostream>
#include <unistd.h>
#include<cstdio>
#include<cstring>
#include<sys/types.h>
#include<sys/wait.h>


void ChildWrite(int wfd)
{
  char c = 0;
  int cnt = 0;
  while(true)
  {
    //snprintf(buffer,sizeof(buffer),"I am child, pid: %d, cnt: %d",getpid(),cnt++);
    write(wfd,&c,1);
    printf("child: %d\n",cnt++);
    //sleep(1);
  }
}

void FatherRead(int rfd)
{
  char buffer[1024];
  while(true)
  {
    sleep(100);
    buffer[0] = 0;
    size_t n = read(rfd,buffer,sizeof(buffer)-1);
    if( n > 0)
    {
      buffer[n] = 0;
      std::cout<<"child say: "<<buffer<<std::endl;
    }
  }
}


int main() {
  int fds[2] = {0}; // 0 读 1 写
  int n = pipe(fds);
  if (n < 0) {
    std::cerr << "pipe error" << std::endl;
    return 1;
  }

  pid_t id = fork();
  if (id == 0) {
    close(fds[0]);

    ChildWrite(fds[1]);

    close(fds[1]);
    exit(0);
  }

  close(fds[1]);

  FatherRead(fds[0]);
  waitpid(id, nullptr, 0);
  close(fds[0]);
  return 0;
}
