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
        printf("子进程运行：PID = %d\n",getpid());
        sleep(1);
        printf("子进程正在进行一系列操作...\n");
        sleep(2);
        exit(44);
    }
    else if (pid > 0)
    {
        int status;
        pid_t ret_pid = wait(&status);
        if(WIFEXITED(status))
        {
            printf("子进程PID：%d, 正常终止，状态码：%d\n",ret_pid,WEXITSTATUS(status));
        }
    }
    return 0;
}