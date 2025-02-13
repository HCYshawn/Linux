#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        //子进程
        printf("子进程开始：PID = %d\n",getpid());
        sleep(2);
        printf("子进程结束\n");
    }
    else if (pid > 0)
    {
        int status;
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("子进程正常终止，状态码：%d\n",WEXITSTATUS(status));
        }
    }
    return 0;
}