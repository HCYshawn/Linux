#include "common.hpp"

#include <cerrno>
#include <cstring>
#include <iostream>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

const char *CommandToString(std::int32_t command)
{
    switch (command)
    {
    case COMMAND_PRINT_LOG:
        return "打印日志任务";
    case COMMAND_PROCESS_DATA:
        return "处理数据任务";
    case COMMAND_FLUSH_CACHE:
        return "刷新缓存任务";
    case COMMAND_EXIT:
        return "退出任务";
    default:
        return "未知任务";
    }
}

void ExecuteTask(const Task &task)
{
    pid_t pid = getpid();
    std::cout << "[worker pid= " << pid << "] "
              << "receive task: "
              << "task_id=" << task.task_id
              << ", command=" << task.command
              << ", meaning=" << CommandToString(task.command)
              << std::endl;

    switch (task.command)
    {
    case COMMAND_PRINT_LOG:
        std::cout << "[worker pid= " << pid << "] "
                  << "执行：打印日志任务"
                  << std::endl;
        usleep(600 * 1000);
        break;

    case COMMAND_PROCESS_DATA:
        std::cout << "[worker pid= " << pid << "] "
                  << "执行：处理数据任务"
                  << std::endl;
        usleep(800 * 1000);
        break;

    case COMMAND_FLUSH_CACHE:
        std::cout << "[worker pid= " << pid << "] "
                  << "执行：刷新缓存任务"
                  << std::endl;
        usleep(400 * 1000);
        break;

    default:
        std::cout << "[worker pid= " << pid << "] "
                  << "执行：未知任务"
                  << std::endl;
        break;
    }
}

int main()
{
    pid_t pid = getpid();
    std::cout << "[worker pid= " << pid << "] "
              << "opening FIFO..."
              << std::endl;

    int fd = open(TASK_FIFO_PATH, O_RDONLY);
    if (fd == -1)
    {
        std::cerr << "[worker pid= " << pid << "] "
                  << "open failed: "
                  << std::strerror(errno)
                  << std::endl;
        return 1;
    }

    std::cout << "[worker pid= " << pid << "] "
              << "connected, waiting for tasks..."
              << std::endl;

    while (true)
    {
        Task task{};

        ssize_t n;

        do
        {
            n = read(fd, &task, sizeof(task));
        } while (n == -1 && errno == EINTR);

        if (n == 0)
        {
            std::cout << "[worker pid= " << pid << "] "
                      << "dispatcher closed FIFO, exit"
                      << std::endl;
            break;
        }

        if (n == -1)
        {
            std::cerr << "[worker pid= " << pid << "] "
                      << "read failed: "
                      << std::strerror(errno)
                      << std::endl;
            break;
        }

        if (n != static_cast<ssize_t>(sizeof(task)))
        {
            std::cerr << "[worker pid= " << pid << "] "
                      << "protocol error: expected "
                      << sizeof(task)
                      << " bytes, but read "
                      << n
                      << " bytes"
                      << std::endl;
            break;
        }

        if (task.command == COMMAND_EXIT)
        {
            std::cout << "[worker pid= " << pid << "] "
                      << "receive exit task, exit"
                      << std::endl;
            break;
        }

        ExecuteTask(task);
    }
    close(fd);
    return 0;
}
