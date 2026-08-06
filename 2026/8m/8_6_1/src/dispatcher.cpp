#include "common.hpp"

#include <cerrno>
#include <cstddef>
#include <cstring>
#include <iostream>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool CreateTaskFifo()
{
    //创建FIFO
    if (mkfifo(TASK_FIFO_PATH, 0666) == 0)
    {
        std::cout << "[dispatcher] created FIFO: "
                  << TASK_FIFO_PATH << std::endl;
        return true;
    }

    //创建失败返回
    if (errno != EEXIST)
    {
        std::cerr << "[dispatcher] mkfifo failed: "
                  << std::strerror(errno) << std::endl;
        return false;
    }

    //读取文件属性存入st
    struct stat st;
    if (stat(TASK_FIFO_PATH, &st) == -1)
    {
        std::cerr << "[dispatcher] stat failed: "
                  << std::strerror(errno) << std::endl;
        return false;
    }

    //判断st是否为FIFO文件
    if (!S_ISFIFO(st.st_mode))
    {
        std::cout << "[dispatcher] path exists, but it is not FIFO: "
                  << TASK_FIFO_PATH << std::endl;
        return false;
    }

    std::cout << "[dispatcher] FIFO already exists: " << TASK_FIFO_PATH << std::endl;

    return true;
}

bool WriteTask(int fd, const Task &task)
{
    //write写字节，将task转为连续的8字节数据
    const char *buffer = reinterpret_cast<const char *>(&task);
    std::size_t total = 0;  //total即成功写入字节数
    
    //循环写入以确保真正写入task的8个字节数据
    while (total < sizeof(Task))
    {
        ssize_t n = write(fd, buffer + total, sizeof(Task) - total);

        if (n > 0)
        {
            total += static_cast<std::size_t>(n);
            continue;
        }

        //判断信号中断
        if (n == -1 && errno == EINTR)
        {
            continue;
        }
        std::cerr << "[dispatcher] write failed: "
                  << std::strerror(errno) << std::endl;
        return false;
    }
    return true;
}

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

int main()
{
    if (!CreateTaskFifo())
    {
        return 1;
    }

    std::cout << "[dispatcher] waiting for reader..." << std::endl;

    int fd = open(TASK_FIFO_PATH, O_WRONLY);
    if (fd == -1)
    {
        std::cerr << "[dispatcher] open failed: "
                  << std::strerror(errno) << std::endl;

        unlink(TASK_FIFO_PATH);
        return 2;
    }

    std::cout << "[dispatcher] reader connected, start sending tasks"
              << std::endl;

    const int task_count = 12;

    for (int i = 1; i <= task_count; ++i)
    {
        Task task;
        task.task_id = i;
        task.command = (i - 1) % 3 + 1;

        if (!WriteTask(fd, task))
        {
            close(fd);
            unlink(TASK_FIFO_PATH);
            return 3;
        }

        std::cout << "[dispatcher] sent task: "
                  << "task_id=" << task.task_id
                  << ", command=" << task.command
                  << ", meaning=" << CommandToString(task.command)
                  << std::endl;

        usleep(200 * 1000);
    }

    std::cout << "[dispatcher] all tasks sent" << std::endl;

    close(fd);

    std::cout << "[dispatcher] write end closed" << std::endl;

    if (unlink(TASK_FIFO_PATH) == -1)
    {
        std::cerr << "[dispatcher] unlink failed: "
                  << std::strerror(errno) << std::endl;
        return 4;
    }

    std::cout << "[dispatcher] removed FIFO node: "
              << TASK_FIFO_PATH << std::endl;

    return 0;
}