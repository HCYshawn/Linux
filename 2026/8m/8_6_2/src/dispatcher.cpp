#include "common.hpp"

#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// 管道创建
bool CreateFifo(const char *path, const char *name)
{
    // 创建FIFO
    if (mkfifo(path, 0666) == 0)
    {
        std::cout << "[dispatcher] created " << name << ": "
                  << path << std::endl;
        return true;
    }

    // 创建失败返回
    if (errno != EEXIST)
    {
        std::cerr << "[dispatcher] mkfifo " << name << " failed: "
                  << std::strerror(errno) << std::endl;
        return false;
    }

    // 读取文件属性存入st
    struct stat st;
    if (stat(path, &st) == -1)
    {
        std::cerr << "[dispatcher] stat " << name << " failed: "
                  << std::strerror(errno) << std::endl;
        return false;
    }

    // 判断st是否为FIFO文件
    if (!S_ISFIFO(st.st_mode))
    {
        std::cout << "[dispatcher] path exists, but it is not FIFO: "
                  << path << std::endl;
        return false;
    }

    std::cout << "[dispatcher] " << name << " already exists: " << path << std::endl;

    return true;
}

// 负责创建两个FIFO
bool CreateAllFifos()
{
    if (!CreateFifo(TASK_FIFO_PATH, "task_fifo"))
    {
        return false;
    }

    if (!CreateFifo(RESULT_FIFO_PATH, "result_fifo"))
    {
        // 避免管道不全
        unlink(TASK_FIFO_PATH);
        return false;
    }

    return true;
}

// 统一清理FIFO
void RemoveAllFifos()
{
    unlink(TASK_FIFO_PATH);
    unlink(RESULT_FIFO_PATH);
}

// 通过此函数更改fd的属性，即修改阻塞状态
bool SetFdBlocking(int fd)
{
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1)
    {
        std::cerr << "[dispatcher] fcntl F_GETFL failed: "
                  << std::strerror(errno) << std::endl;
        return false;
    }

    flags &= ~O_NONBLOCK;

    if (fcntl(fd, F_SETFL, flags) == -1)
    {
        std::cerr << "[dispatcher] fcntl F_SETFL failed: "
                  << std::strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool WriteFull(int fd, const void *data, std::size_t size)
{
    // write写字节，将task转为连续的8字节数据
    const char *buffer = static_cast<const char *>(data);
    std::size_t total = 0; // total即成功写入字节数

    // 循环写入以确保真正写入task的8个字节数据
    while (total < size)
    {
        ssize_t n = write(fd, buffer + total, size - total);

        if (n > 0)
        {
            total += static_cast<std::size_t>(n);
            continue;
        }

        // 判断信号中断
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

bool ReadFull(int fd, void *data, std::size_t size)
{
    char *buffer = static_cast<char *>(data);
    std::size_t total = 0;

    while (total < size)
    {
        ssize_t n = read(fd, buffer + total, size - total);

        if (n > 0)
        {
            total += static_cast<std::size_t>(n);
            continue;
        }

        if (n == 0)
        {
            std::cerr << "[dispatcher] result_fifo closed unexpectedly"
                      << std::endl;
            return false;
        }

        if (n == -1 && errno == EINTR)
        {
            continue;
        }

        std::cerr << "[dispatcher] read failed: "
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

const char *StatusToString(std::int32_t status)
{
    switch (status)
    {
    case STATUS_OK:
        return "成功";
    case STATUS_FAILED:
        return "失败";
    default:
        return "未知状态";
    }
}

int main()
{
    if (!CreateAllFifos())
    {
        return 1;
    }

    // 回复管道
    // 先不阻塞打开
    int result_fd = open(RESULT_FIFO_PATH, O_RDONLY | O_NONBLOCK);
    if (result_fd == -1)
    {
        std::cerr << "[dispatcher] open result_fifo failed: "
                  << std::strerror(errno) << std::endl;
        RemoveAllFifos();
        return 2;
    }

    // 阻塞
    if (!SetFdBlocking(result_fd))
    {
        close(result_fd);
        RemoveAllFifos();
        return 3;
    }

    std::cout << "[dispatcher] result_fifo read end opened"
              << std::endl;

    std::cout << "[dispatcher] waiting for worker to open task_fifo..."
              << std::endl;

    // 打开任务管道
    int task_fd = open(TASK_FIFO_PATH, O_WRONLY);
    if (task_fd == -1)
    {
        std::cerr << "[dispatcher] open task_fifo failed: "
                  << std::strerror(errno) << std::endl;
        close(result_fd);
        RemoveAllFifos();
        return 4;
    }

    std::cout << "[dispatcher] worker connected, start sending tasks"
              << std::endl;

    const int task_count = 12;

    // 通过任务管道派发任务
    for (int i = 1; i <= task_count; ++i)
    {
        Task task;
        task.task_id = i;
        task.command = (i - 1) % 3 + 1;

        if (!WriteFull(task_fd, &task, sizeof(task)))
        {
            close(task_fd);
            close(result_fd);
            RemoveAllFifos();
            return 5;
        }

        std::cout << "[dispatcher] sent task: "
                  << "task_id=" << task.task_id
                  << ", command=" << task.command
                  << ", meaning=" << CommandToString(task.command)
                  << std::endl;

        usleep(200 * 1000);
    }

    std::cout << "[dispatcher] all tasks sent, waiting for results..."
              << std::endl;

    // 通过回复管道收集信息
    for (int i = 1; i <= task_count; ++i)
    {
        Result result{};

        if (!ReadFull(result_fd, &result, sizeof(result)))
        {
            close(task_fd);
            close(result_fd);
            RemoveAllFifos();
            return 6;
        }

        std::cout << "[dispatcher] receive result: "
                  << "worker_pid=" << result.worker_pid
                  << ", task_id=" << result.task_id
                  << ", command=" << result.command
                  << ", meaning=" << CommandToString(result.command)
                  << ", status=" << StatusToString(result.status)
                  << std::endl;
    }

    std::cout << "[dispatcher] all results received"
              << std::endl;

    close(task_fd);
    close(result_fd);

    std::cout << "[dispatcher] fifo fds closed"
              << std::endl;

    RemoveAllFifos();

    std::cout << "[dispatcher] fifo nodes removed"
              << std::endl;

    return 0;
}