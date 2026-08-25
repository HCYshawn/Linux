#include "Thread.hpp"
#include <unistd.h>

using namespace ThreadModlue;

void Count(int cnt)
{
    while (cnt--)
    {
        std::cout << "我是一个新线程" << std::endl;
        sleep(1);
    }
}

int main()
{
    int cnt = 10;
    Thread<int> t(Count, cnt);

    t.Start();
    // t.Detach();
    // sleep(5);

    // t.Stop();

    // sleep(5);

    t.Join();
    return 0;
}