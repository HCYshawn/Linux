#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>

void handler(int signum)
{
    std::cout << "hello signal: " << signum << std::endl;

    while (true)
    {
        sigset_t pending;
        sigpending(&pending);
        for (int i = 31; i >= 1; i--)
        {
            if (sigismember(&pending, i))
            {
                std::cout << "1";
            }
            else
                std::cout << "0";
        }
        std::cout << std::endl;
        sleep(1);
    }

    exit(0);
}

int main()
{
    struct sigaction act, oact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, 3);
    sigaddset(&act.sa_mask, 4);
    act.sa_flags = 0;

    // 对2号信号进行捕捉
    sigaction(SIGINT, &act, &oact);

    while (true)
    {
        std::cout << "my pid: " << getpid() << std::endl;
        sleep(1);
    }
    return 0;
}