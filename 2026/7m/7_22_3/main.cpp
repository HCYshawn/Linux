#include<iostream>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    int fd = open("log.txt", O_CREAT|O_WRONLY|O_TRUNC,0666);
    if(fd < 0)exit(1);
    dup2(fd,1);

    printf("fd: %d\n",fd);
    printf("hello\n");
    printf("hello\n");
    printf("hello\n");
    printf("hello\n");
    fprintf(stdout,"hello\n");
    fprintf(stdout,"hello\n");
    fprintf(stdout,"hello\n");
    fprintf(stdout,"hello\n");

    const char* msg = "hello world\n";
    write(fd,msg,strlen(msg));
    return 0;
}