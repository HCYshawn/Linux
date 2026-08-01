#include "ProcessPool.hpp"

int main()
{
    ProcessPool pp(gdefaultnum);

    pp.Start();

    int cnt = 10;
    while(cnt--)
    {
        pp.Run();
        sleep(1);
    }

    pp.Stop();
    return 0;
}
