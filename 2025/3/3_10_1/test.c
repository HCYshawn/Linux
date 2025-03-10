#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{
    // 使用库缓冲区
    FILE *fp = fopen("output.txt", "w");
    fprintf(fp, "Hello, World!\n");
    fflush(fp);  // 将库缓冲区数据刷新到系统缓冲区
    fclose(fp);  // 关闭文件时刷新库缓冲区

    // 使用系统缓冲区
    int fd = open("output.txt", O_WRONLY | O_APPEND);
    write(fd, "Hello, Kernel!\n", 15);  // 数据写入系统缓冲区
    fsync(fd);  // 将系统缓冲区数据刷新到磁盘
    close(fd);

    return 0;
}