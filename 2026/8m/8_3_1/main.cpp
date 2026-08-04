#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0)
    {
        // child：只读
        close(fd[1]);

        char buf[1024] = {0};

        while (true)
        {
            ssize_t n = read(fd[0], buf, sizeof(buf) - 1);

            if (n > 0)
            {
                buf[n] = '\0';
                std::cout << "child read: " << buf << std::endl;
            }
            else if (n == 0)
            {
                std::cout << "child read EOF, writer closed" << std::endl;
                break;
            }
            else
            {
                perror("read");
                break;
            }
        }

        close(fd[0]);
        return 0;
    }
    else
    {
        // parent：只写
        close(fd[0]);

        const char *msg = "hello pipe";
        write(fd[1], msg, 10);

        sleep(1);

        // 父进程关闭写端
        close(fd[1]);

        wait(nullptr);
    }

    return 0;
}