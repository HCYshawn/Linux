#include <iostream>
#include <vector>
#include <functional>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void handler(int sig)
{
    std::cout << "hello sig: " << sig << std::endl;
    signal(2, SIG_DFL);
    std::cout << "恢复处理动作" << std::endl;
}

int main()
{
    signal(2, handler);
    // signal(2, SIG_IGN);

    while (true)
    {
        sleep(1);
        std::cout << "." << std::endl;
    }

    return 0;
}