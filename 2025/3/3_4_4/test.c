#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>

//自定义的SIGTERM信号处理函数
void handle_sigterm(int sig)
{
    printf("接收到SIGTERM信号，进程终止\n");
    exit(0);//正常退出程序
}

int main()
{
    //注册SIGTERM信号的处理函数
    signal(SIGTERM,handle_sigterm);

    //定义一个计数，循环10次后程序自动kill自己，此时捕获SIGTERM信号，打印该信息
    int i = 10;
    while(1)
    {
        printf("程序正在运行...\n");
        i--;

        sleep(2);
        
        if(!i)
        {
            kill(getpid(),SIGTERM);
        }
    }
    return 0;
}