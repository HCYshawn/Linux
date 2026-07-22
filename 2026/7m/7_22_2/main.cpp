#include<iostream>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    umask(0);
    int fd = open("log.txt",O_CREAT | O_WRONLY | O_TRUNC,0666);
    if(fd < 0)
    {
        perror("open");
        return 1;
    }
    printf("fd: %d\n",fd);

    const char* msg = "hello open\n";
    int cnt = 5;
    while(cnt)
    {
        write(fd,msg,strlen(msg));
        cnt--;
    }

    close(fd);
    return 0;
}
