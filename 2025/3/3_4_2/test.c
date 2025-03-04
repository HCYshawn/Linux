#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
    int ret = 0;
    char *p = (char*)malloc(1000*1000*1000*4);
    if(p==NULL)
    {
        //errno记录错误码，传至strerror得到错误信息
        printf("malloc error, %d:%s\n",errno,strerror(errno));
        //返回错误码，让父进程得到返回信息
        ret = errno;
    }
    else
    {
        printf("malloc success\n");
    }
    return ret;
}