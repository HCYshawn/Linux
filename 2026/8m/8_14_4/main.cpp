#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>

void WaitAll(int num)
{
    while (true)
    {
        pid_t n = waitpid(-1, nullptr, WNOHANG);
        if (n == 0)
        {
            break;
        }
        else if (n < 0)
        {
            std::cout << "waitpid error" << std::endl;
            break;
        }
    }
    std::cout << "father get a signal: " << num << std::endl;
}

int main()
{
    signal(SIGCHLD, WaitAll);

    for (int i = 0; i < 10; i++)
    {
        pid_t id = fork();
        if (id == 0)
        {
            sleep(3);
            std::cout << "I am child, exit" << std::endl;

            exit(3);
        }
    }

    while (true)
    {
        std::cout << "I am father, exit" << std::endl;
        sleep(1);
    }

    return 0;
}
