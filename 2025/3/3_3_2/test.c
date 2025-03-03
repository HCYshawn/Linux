#include<stdio.h>
#include<stdlib.h>

int g_unval;
int g_val = 100;
int main(int argc,char*argv[],char*envp[])
{
    printf("code addr: %p\n",main);//代码区
    char* str = "hello world";
    printf("red only addr: %p\n",str);//只读常量区
    printf("init addr: %p\n",&g_val);//初始化数据
    printf("uninit addr: %p\n",&g_unval);//未初始化数据
    int *p = (int*)malloc(10);
    printf("heap addr: %p\n",p);//堆区
    printf("stack addr: %p\n",&str);//栈区
    printf("stack addr: %p\n",&p);//栈区
    for(int i = 0;i<argc;i++)
    {
        printf("args addr: %p\n",argv[i]);//命令行参数
    }
    int i = 0;
    while(i)
    {
        printf("env addr: %p\n",envp[i]);//环境变量
        i++;
    }
    return 0;
}