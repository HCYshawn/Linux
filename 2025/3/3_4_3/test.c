#include<stdio.h>
#include<stdlib.h>

int main()
{
    printf("遇到严重错误，程序终止！\n");
    abort();//异常终止
    return 0;//不会被执行
}