#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *fstr = "hello fwrite\n";
    const char *str = "hello write\n";

    // C语言接口
    printf("hello printf\n");
    fflush(stdout);  // 刷新缓冲区
    fprintf(stdout, "hello fprintf\n");
    fflush(stdout);  // 刷新缓冲区
    fwrite(fstr, strlen(fstr), 1, stdout);
    fflush(stdout);  // 刷新缓冲区

    // 操作系统提供的系统接口
    write(1, str, strlen(str));

    return 0;
}