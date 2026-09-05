#pragma once
#include <iostream>
#include <unistd.h>
#include <functional>
#include "Log.hpp"

using namespace LogModule;

using task_t = std::function<void()>;

void Download()
{
    LOG(LogLevel::DEBUG) << "我是一个下载任务...";
}

class Task
{
public:
    Task(int x, int y) : _x(x), _y(y) {}
    void Execute()
    {
        _result = _x + _y;
    }
    int X() { return _x; }
    int Y() { return _y; }

    int Result()
    {
        return _result;
    }

    ~Task() {}

private:
    int _x;
    int _y;
    int _result;
};