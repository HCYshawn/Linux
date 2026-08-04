#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <ctime>
#include <cerrno>

struct Channel
{
    pid_t pid;
    int wfd; // 父进程保留的写端
};

void ExecuteTask(int cmd)
{
    switch (cmd)
    {
    case 1:
        std::cout << "pid[" << getpid() << "] 执行任务1：打印日志" << std::endl;
        break;
    case 2:
        std::cout << "pid[" << getpid() << "] 执行任务2：处理数据" << std::endl;
        break;
    case 3:
        std::cout << "pid[" << getpid() << "] 执行任务3：刷新缓存" << std::endl;
        break;
    default:
        std::cout << "pid[" << getpid() << "] 收到未知任务：" << cmd << std::endl;
        break;
    }
}

void WorkerLoop(int rfd)
{
    while (true)
    {
        int cmd = 0;
        ssize_t n = read(rfd, &cmd, sizeof(cmd));

        if (n == sizeof(cmd))
        {
            ExecuteTask(cmd);
        }
        else if (n == 0)
        {
            // 所有写端关闭，读到 EOF
            std::cout << "pid[" << getpid() << "] 退出" << std::endl;
            break;
        }
        else
        {
            if (errno == EINTR)
            {
                continue;
            }

            perror("read");
            break;
        }
    }

    close(rfd);
}

int main()
{
    const int process_num = 3;
    std::vector<Channel> channels;

    srand(time(nullptr) ^ getpid());

    for (int i = 0; i < process_num; ++i)
    {
        int pipefd[2] = {0};

        if (pipe(pipefd) < 0)
        {
            perror("pipe");
            return 1;
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            return 2;
        }
        else if (pid == 0)
        {
            // 子进程：关闭当前管道写端
            close(pipefd[1]);

            // 子进程会继承父进程之前保存的写端，需要关闭
            for (const auto &ch : channels)
            {
                close(ch.wfd);
            }

            WorkerLoop(pipefd[0]);
            return 0;
        }
        else
        {
            // 父进程：关闭当前管道读端，只保留写端
            close(pipefd[0]);

            channels.push_back({pid, pipefd[1]});
        }
    }

    // 父进程派发 10 个任务
    for (int i = 0; i < 10; ++i)
    {
        int index = i % channels.size();
        int cmd = rand() % 3 + 1;

        std::cout << "parent send task " << cmd
                  << " to child " << channels[index].pid << std::endl;

        write(channels[index].wfd, &cmd, sizeof(cmd));

        sleep(1);
    }

    // 父进程关闭所有写端，通知子进程退出
    for (auto &ch : channels)
    {
        close(ch.wfd);
    }

    // 回收子进程
    for (auto &ch : channels)
    {
        waitpid(ch.pid, nullptr, 0);
    }

    return 0;
}