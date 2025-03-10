#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() 
{
    const char *fstr = "hello fwrite\n";
    const char *str = "hello write\n";

    // C语言接口
    printf("hello printf\n");               // stdout -> 1
    fprintf(stdout, "hello fprintf\n");     // stdout -> 1
    fwrite(fstr, strlen(fstr), 1, stdout); // stdout -> 1

    // 操作系统提供的系统接口
    write(1, str, strlen(str));            // 直接写入文件描述符 1（stdout）

    fork();  // 创建子进程

    return 0;
}