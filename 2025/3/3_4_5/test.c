#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    pid_t pid1 = fork();
    //子进程 1
    if(pid1 == 0)
    {
        printf("子进程 1 正在运行...\n");
        sleep(2);
        printf("子进程 1 正在退出...\n");
        exit(1);
    }

    //子进程 2
    pid_t pid2 = fork();
    if(pid2 == 0)
    {
        printf("子进程 2 正在运行...\n");
        sleep(4);
        printf("子进程 2 正在退出...\n");
        exit(2);
    }

    //父进程
    int status;
    pid_t child_pid;
    //循环等待所有子进程
    while((child_pid = waitpid(-1, &status, 0)) > 0)
    {
        if(WIFEXITED(status))
        {
            printf("子进程 %d 退出, 状态: %d\n",child_pid,WEXITSTATUS(status));
        }
    }
    return 0;
}