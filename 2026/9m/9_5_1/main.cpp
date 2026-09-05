#include "Log.hpp"
#include "ThreadPool.hpp"
#include "Task.hpp"
#include <memory>

using namespace LogModule;
using namespace ThreadPoolModule;

int main()
{
    Enable_Console_Log_Strategy();

    int count = 10;
    while (count)
    {
        sleep(1);
        ThreadPool<task_t>::GetInstance()->Enqueue(Download);

        count--;
    }

    ThreadPool<task_t>::GetInstance()->Stop();
    ThreadPool<task_t>::GetInstance()->Join();

    return 0;
}