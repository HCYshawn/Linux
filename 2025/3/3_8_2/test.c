#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    printf("stdin: %d\n",stdin->_fileno);
    printf("stdout: %d\n",stdout->_fileno);
    printf("stderr: %d\n",stderr->_fileno);
    int fd1 = open("log1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    int fd2 = open("log2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    int fd3 = open("log3.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    int fd4 = open("log4.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if(fd1 < 0)exit(1);
    if(fd2 < 0)exit(1);
    if(fd3 < 0)exit(1);
    if(fd4 < 0)exit(1);

    printf("fd1: %d\n", fd1);
    printf("fd2: %d\n", fd2);
    printf("fd3: %d\n", fd3);
    printf("fd4: %d\n", fd4);
    return 0;
}