#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>



int main()
{
    signal(SIGCHLD, SIG_IGN);

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
