#include "common.hpp"

#include <cerrno>
#include <cstddef>
#include <cstdint>
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

bool WriteFull(int fd, const void *data, std::size_t size)
{
    const char *buffer = static_cast<const char *>(data);
    std::size_t total = 0;

    while (total < size)
    {
        ssize_t n = write(fd, buffer + total, size - total);

        if (n > 0)
        {
            total += static_cast<std::size_t>(n);
            continue;
        }

        if (n == -1 && errno == EINTR)
        {
            continue;
        }

        std::cerr << "[worker pid=" << getpid() << "] "
                  << "write failed: "
                  << std::strerror(errno)
                  << std::endl;
        return false;
    }

    return true;
}

// 执行任务并判定成功or失败
std::int32_t ExecuteTask(const Task &task)
{
    pid_t pid = getpid();

    std::cout << "[worker pid=" << pid << "] "
              << "receive task: "
              << "task_id=" << task.task_id
              << ", command=" << task.command
              << ", meaning=" << CommandToString(task.command)
              << std::endl;

    switch (task.command)
    {
    case COMMAND_PRINT_LOG:
        std::cout << "[worker pid=" << pid << "] "
                  << "执行：打印日志任务"
                  << std::endl;
        usleep(600 * 1000);
        return STATUS_OK;

    case COMMAND_PROCESS_DATA:
        std::cout << "[worker pid=" << pid << "] "
                  << "执行：处理数据任务"
                  << std::endl;
        usleep(800 * 1000);
        return STATUS_OK;

    case COMMAND_FLUSH_CACHE:
        std::cout << "[worker pid=" << pid << "] "
                  << "执行：刷新缓存任务"
                  << std::endl;
        usleep(400 * 1000);
        return STATUS_OK;

    default:
        std::cout << "[worker pid=" << pid << "] "
                  << "执行：未知任务"
                  << std::endl;
        return STATUS_FAILED;
    }
}

//将结果打包
bool SendResult(int result_fd, const Task &task, std::int32_t status)
{
    Result result;
    result.worker_pid = static_cast<std::int32_t>(getpid());
    result.task_id = task.task_id;
    result.command = task.command;
    result.status = status;

    if (!WriteFull(result_fd, &result, sizeof(result)))
    {
        return false;
    }

    std::cout << "[worker pid=" << getpid() << "] "
              << "send result: "
              << "task_id=" << result.task_id
              << ", command=" << result.command
              << ", status=" << StatusToString(result.status)
              << std::endl;

    return true;
}

int main()
{
    pid_t pid = getpid();

    std::cout << "[worker pid=" << pid << "] "
              << "opening task_fifo..."
              << std::endl;

    // 任务管道
    int task_fd = open(TASK_FIFO_PATH, O_RDONLY);
    if (task_fd == -1)
    {
        std::cerr << "[worker pid=" << pid << "] "
                  << "open task_fifo failed: "
                  << std::strerror(errno)
                  << std::endl;
        return 1;
    }

    std::cout << "[worker pid=" << pid << "] "
              << "task_fifo connected"
              << std::endl;

    std::cout << "[worker pid=" << pid << "] "
              << "opening result_fifo..."
              << std::endl;

    // 回复管道
    int result_fd = open(RESULT_FIFO_PATH, O_WRONLY);
    if (result_fd == -1)
    {
        std::cerr << "[worker pid=" << pid << "] "
                  << "open result_fifo failed: "
                  << std::strerror(errno)
                  << std::endl;

        close(task_fd);
        return 2;
    }

    std::cout << "[worker pid=" << pid << "] "
              << "result_fifo connected, waiting for tasks..."
              << std::endl;

    while (true)
    {
        Task task{};

        ssize_t n;
        do
        {
            n = read(task_fd, &task, sizeof(task));
        } while (n == -1 && errno == EINTR);

        if (n == 0)
        {
            std::cout << "[worker pid=" << pid << "] "
                      << "dispatcher closed task_fifo, exit"
                      << std::endl;
            break;
        }

        if (n == -1)
        {
            std::cerr << "[worker pid=" << pid << "] "
                      << "read task failed: "
                      << std::strerror(errno)
                      << std::endl;
            break;
        }

        if (n != static_cast<ssize_t>(sizeof(task)))
        {
            std::cerr << "[worker pid=" << pid << "] "
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
            std::cout << "[worker pid=" << pid << "] "
                      << "receive exit task, exit"
                      << std::endl;
            break;
        }

        std::int32_t status = ExecuteTask(task);

        if (!SendResult(result_fd, task, status))
        {
            break;
        }
    }

    close(task_fd);
    close(result_fd);

    std::cout << "[worker pid=" << pid << "] "
              << "fifo fds closed"
              << std::endl;

    return 0;
}