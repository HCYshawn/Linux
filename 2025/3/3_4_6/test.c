#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

void signald_handler(int sig)
{
    int status;
    pid_t pid = wait(&status);
    if(pid > 0 && WIFEXITED(status))
    {
        printf("子进程 %d 退出, 退出信息：%d\n",pid,WEXITSTATUS(status));
    }
}

int main()
{
    signal(SIGCHLD,signald_handler);

    pid_t pid = fork();
    if(pid == 0)
    {
        printf("子进程运行中...\n");
        sleep(3);
        printf("子进程退出中...\n");
        exit(42);
    }

    printf("父进程正在做其他工作...\n");

    while(1)
    {
        sleep(1);
    }
    return 0;
}