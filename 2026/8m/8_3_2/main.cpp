#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main()
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0)
    {
        // child：关闭读端和写端，模拟没人读
        close(fd[0]);
        close(fd[1]);
        return 0;
    }
    else
    {
        // parent：关闭自己的读端，只写
        close(fd[0]);

        sleep(1);

        const char* msg = "hello";
        while (true)
        {
            std::cout << "parent writing..." << std::endl;
            write(fd[1], msg, strlen(msg));
            sleep(1);
        }

        wait(nullptr);
    }

    return 0;
}