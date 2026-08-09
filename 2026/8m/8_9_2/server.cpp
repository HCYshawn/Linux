#include "shm.hpp"

int main()
{
    Shm shm(pathname, projid, CREATER);

    char *mem = (char *)shm.VirtualAddr();
    while (true)
    {
        printf("%s\n", mem);
        sleep(1);
    }
    return 0;
}