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
    for (int i = 1; i < 32; i++)
        signal(i, handlerSig);

    for (int i = 1; i < 32; i++)
    {
        sleep(1);
        if (i == 9 || i == 19)
        {
            continue;
        }
        raise(i);
        }
    int cnt = 0;
    while (true)
    {
        std::cout << "cnt: " << cnt++ << ", pid: " << getpid() << std::endl;
        sleep(1);
    }
    return 0;
}
