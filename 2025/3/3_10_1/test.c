#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{
    // ʹ�ÿ⻺����
    FILE *fp = fopen("output.txt", "w");
    fprintf(fp, "Hello, World!\n");
    fflush(fp);  // ���⻺��������ˢ�µ�ϵͳ������
    fclose(fp);  // �ر��ļ�ʱˢ�¿⻺����

    // ʹ��ϵͳ������
    int fd = open("output.txt", O_WRONLY | O_APPEND);
    write(fd, "Hello, Kernel!\n", 15);  // ����д��ϵͳ������
    fsync(fd);  // ��ϵͳ����������ˢ�µ�����
    close(fd);

    return 0;
}