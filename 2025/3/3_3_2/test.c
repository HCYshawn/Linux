#include<stdio.h>
#include<stdlib.h>

int g_unval;
int g_val = 100;
int main(int argc,char*argv[],char*envp[])
{
    printf("code addr: %p\n",main);//������
    char* str = "hello world";
    printf("red only addr: %p\n",str);//ֻ��������
    printf("init addr: %p\n",&g_val);//��ʼ������
    printf("uninit addr: %p\n",&g_unval);//δ��ʼ������
    int *p = (int*)malloc(10);
    printf("heap addr: %p\n",p);//����
    printf("stack addr: %p\n",&str);//ջ��
    printf("stack addr: %p\n",&p);//ջ��
    for(int i = 0;i<argc;i++)
    {
        printf("args addr: %p\n",argv[i]);//�����в���
    }
    int i = 0;
    while(i)
    {
        printf("env addr: %p\n",envp[i]);//��������
        i++;
    }
    return 0;
}