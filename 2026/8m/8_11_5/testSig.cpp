#include <iostream>
#include <vector>
#include <functional>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void Sched()
{
    std::cout << "我是进程调度" << std::endl;
}

void MemManager()
{
    std::cout << "我是周期性内存管理，检测是否有内存问题" << std::endl;
}

void Fflush()
{
    std::cout << "我是刷新程序，定期刷新" << std::endl;
}

using func_t = std::function<void()>;

std::vector<func_t> funcs;

void handlerSig(int sig)
{
    std::cout << "##########################" << std::endl;
    for (auto f : funcs)
        f();
    std::cout << "##########################" << std::endl;
    int n = alarm(1);
}

int main()
{
    funcs.push_back(Sched);
    funcs.push_back(MemManager);
    funcs.push_back(Fflush);

    signal(SIGALRM, handlerSig);

    // 设定闹钟
    alarm(1);

    while (true)
    {
        pause();
    }

    return 0;
}