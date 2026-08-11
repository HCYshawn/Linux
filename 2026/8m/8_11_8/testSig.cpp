#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        sleep(2);
        printf("hello core\n");
        printf("hello core\n");
        printf("hello core\n");
        printf("hello core\n");
        int a = 10;
        a /= 0;
        printf("hello core\n");

        exit(1);
    }
    int status = 0;
    waitpid(id, &status, 0);
    printf("signal: %d, exit code: %d, core dump: %d\n", (status & 0x7F), (status >> 8) & 0xFF, (status >> 7) & 0x1);
    return 0;
}
