#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int cnt = 0;

void handlerSig(int sig)
{
    std::cout << "获得了一个信号: " << sig << " cnt: " << cnt << std::endl;
    exit(13);
}

int main()
{
    // for (int i = 1; i < 32; i++)
    //     signal(i, handlerSig);

    signal(SIGALRM, handlerSig);

    // 设定闹钟
    alarm(1);

    while (true)
    {
        cnt++;
        // std::cout << "count: " << cnt++ << std::endl;
    }

    return 0;
}