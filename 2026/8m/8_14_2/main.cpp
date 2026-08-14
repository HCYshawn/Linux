#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>

volatile int flag = 0;

void handler(int signum)
{
    std::cout << "修改 flag " << flag << " -> " << "1" << std::endl;
    flag = 1;
}

int main()
{
    signal(2, handler);

    while (!flag)
        ;
    std::cout << "process quit normal! " << std::endl;
    return 0;
}
