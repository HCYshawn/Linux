#include "shm.hpp"

int main()
{
    Shm shm(pathname, projid, USER);
    char *mem = (char *)shm.VirtualAddr();

    for (char c = 'A'; c <= 'Z'; c++)
    {
        mem[c-'A'] =  c;
        sleep(1);
    }
    return 0;
}