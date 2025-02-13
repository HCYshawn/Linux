#include<signal.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        while(1)
        {
            printf("子进程正在运行：PID = %d\n",getpid());
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        sleep(5);
        printf("终止子进程：PID = %d\n",pid);
        kill(pid,SIGKILL);
    }
    return 0;
}