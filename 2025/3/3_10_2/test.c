#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() 
{
    const char *fstr = "hello fwrite\n";
    const char *str = "hello write\n";

    // C���Խӿ�
    printf("hello printf\n");               // stdout -> 1
    fprintf(stdout, "hello fprintf\n");     // stdout -> 1
    fwrite(fstr, strlen(fstr), 1, stdout); // stdout -> 1

    // ����ϵͳ�ṩ��ϵͳ�ӿ�
    write(1, str, strlen(str));            // ֱ��д���ļ������� 1��stdout��

    fork();  // �����ӽ���

    return 0;
}