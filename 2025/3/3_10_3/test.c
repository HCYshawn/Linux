#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *fstr = "hello fwrite\n";
    const char *str = "hello write\n";

    // C���Խӿ�
    printf("hello printf\n");
    fflush(stdout);  // ˢ�»�����
    fprintf(stdout, "hello fprintf\n");
    fflush(stdout);  // ˢ�»�����
    fwrite(fstr, strlen(fstr), 1, stdout);
    fflush(stdout);  // ˢ�»�����

    // ����ϵͳ�ṩ��ϵͳ�ӿ�
    write(1, str, strlen(str));

    return 0;
}