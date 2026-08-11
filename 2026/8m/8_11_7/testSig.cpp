#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void PrintPending(sigset_t &pending)
{
    printf("我是一个进程(%d), pending: ", getpid());
    for (int signo = 1; signo <= 31; signo++)
    {
        if (sigismember(&pending, signo))
        {
            std::cout << "1";
        }
        else
        {
            std::cout << "0";
        }
    }
    std::cout << std::endl;
}

void handler(int sig)
{
    std::cout << "############################" << std::endl;
    std::cout << "递达 " << sig << "信号! " << std::endl;
    sigset_t pending;
    int m = sigpending(&pending);
    PrintPending(pending);
    std::cout << "############################" << std::endl;
}

int main()
{
    signal(SIGINT, handler);

    // 1. 屏蔽 2 号信号
    sigset_t block, oblock;
    // 清空
    sigemptyset(&block);
    sigemptyset(&oblock);

    sigaddset(&block, SIGINT);
    int n = sigprocmask(SIG_SETMASK, &block, &oblock);

    (void)n;

    int cnt = 0;

    // 4. 重复获取打印过程
    while (true)
    {
        // 2. 获取pending 信号集
        sigset_t pending;
        int m = sigpending(&pending);

        // 3. 打印
        PrintPending(pending);
        if (cnt == 10)
        {
            // 5. 恢复对2号信号的block情况
            sigprocmask(SIG_SETMASK, &oblock, nullptr);
            std::cout << "解除对2号信号的屏蔽" << std::endl;
        }

        sleep(1);
        cnt++;
    }

    return 0;
}
