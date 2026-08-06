#pragma once

#include <cstdint>
#include <type_traits>

// dispatcher -> worker 的任务 FIFO
constexpr const char *TASK_FIFO_PATH = "/tmp/task_fifo";

// worker -> dispatcher 的结果 FIFO
constexpr const char *RESULT_FIFO_PATH = "/tmp/result_fifo";

// 任务命令
enum Command : std::int32_t
{
    COMMAND_EXIT = 0,         // 退出任务
    COMMAND_PRINT_LOG = 1,    // 打印日志任务
    COMMAND_PROCESS_DATA = 2, // 处理数据任务
    COMMAND_FLUSH_CACHE = 3   // 刷新缓存任务
};

// 任务执行状态
enum Status : std::int32_t
{
    STATUS_OK = 0,
    STATUS_FAILED = 1
};

// dispatcher 写入 task_fifo、worker 从 task_fifo 读取的任务
struct Task
{
    std::int32_t task_id;
    std::int32_t command;
};

// worker 写入 result_fifo、dispatcher 从 result_fifo 读取的结果
struct Result
{
    std::int32_t worker_pid;
    std::int32_t task_id;
    std::int32_t command;
    std::int32_t status;
};

// 诊断是否为可拷贝类型
static_assert(std::is_trivially_copyable<Task>::value,
              "Task must be trivially copyable");

static_assert(std::is_trivially_copyable<Result>::value,
              "Result must be trivially copyable");

// 诊断字节数
static_assert(sizeof(Task) == 8,
              "unexpected Task size");

static_assert(sizeof(Result) == 16,
              "Unexpected Result size");