#include <iostream>
#include <mutex>
#include <thread>
#include <string>

class Log
{
public:
    Log() {};
    Log(const Log &log) = delete;
    Log operator=(const Log &log) = delete;

    static Log &GetLog()
    {
        std::call_once(once, init);
        return *log;
    }
    static void init()
    {
        if (!log)
        {
            log = new Log;
        }
    }

    void print(const std::string &msg)
    {
        std::cout << __TIME__ << ' ' << msg << std::endl;
    }

    static Log *log;
    static std::once_flag once;
};

Log *Log::log = nullptr;
std::once_flag Log::once;

void test()
{
    Log::GetLog().print("error");
}

int main()
{
    std::thread t1(test);
    std::thread t2(test);

    t1.join();
    t2.join();
    return 0;
}