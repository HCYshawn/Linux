#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>

void hello()
{
    while (true)
    {
        std::cout << "新线程: hello thread, pid: " << getpid() << std::endl;
        sleep(1);
    }
}

int main()
{
    std::thread t(hello);

    while (true)
    {
        std::cout << "主线程..." << ", pid: " << getpid() << std::endl;
        sleep(1);
    }

    t.join();

    return 0;
}