#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    int fd = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0666);
    if(fd < 0) exit(1);

    dup2(fd, 1);
    close(fd);

    printf("fd: %d\n", fd);
    printf("hello bit\n");
    printf("hello bit\n");
    printf("hello bit\n");
    fprintf(stdout, "hello stdout\n");
    fprintf(stdout, "hello stdout\n");
    fprintf(stdout, "hello stdout\n");
    fprintf(stdout, "hello stdout\n");
    return 0;
}
