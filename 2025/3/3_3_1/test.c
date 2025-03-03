#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    printf("I am running ...\n");
    pid_t id = fork();
    if(id == 0)
    {
        int count = 5;
        while(1)
        {
            printf("I am child... PID:%d, PPID:%d\n",getpid(),getppid());
            sleep(1);
        }
    }
    else if (id>0)
    {
        int count = 5;
        while(count)
        {
            printf("I am father... PID:%d, PPID:%d\n",getpid(),getppid());
            sleep(1);
            count--;
        }
        printf("father quit...\n");
        exit(0);
    }
    return 0;
}