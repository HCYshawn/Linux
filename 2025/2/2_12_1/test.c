#include<stdio.h>
#include<string.h>

int main()
{
    int i = 0;
    for(; i < 200; i++)
    {
        printf("%d->%s\n",i,strerror(i));
    }
    return 0;
}