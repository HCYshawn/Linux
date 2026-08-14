#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>

void Say(int num)
{
    std::cout << "father get a signal: " << num << std::endl;
}

int main()
{
    signal(SIGCHLD, Say);

    pid_t id = fork();
    if (id == 0)
    {
        std::cout << "I am child, exit" << std::endl;
        sleep(3);
        exit(3);
    }
    waitpid(id, nullptr, 0);
    std::cout << "I am father, exit" << std::endl;
    return 0;
}
