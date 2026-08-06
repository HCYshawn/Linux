#pragma once

#include<cstdint>
#include<type_traits>

constexpr const char *TASK_FIFO_PATH = "/tmp/task_fifo";

enum Command : std::int32_t
{
    COMMAND_EXIT = 0,           //退出任务
    COMMAND_PRINT_LOG = 1,      //打印日志任务
    COMMAND_PROCESS_DATA = 2,   //处理数据任务
    COMMAND_FLUSH_CACHE = 3     //刷新缓存任务
};

struct Task
{
    std::int32_t task_id;
    std::int32_t command;
};

static_assert(std::is_trivially_copyable<Task>::value, 
"Task must be trivially copyable");

static_assert(sizeof(Task) == 8, "unexpected Task size");
