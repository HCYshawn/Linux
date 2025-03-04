#include<stdio.h>
#include<stdlib.h>

void print()
{
    printf("running...\n");
    printf("running...\n");
    printf("running...\n");
    printf("running...\n");
    exit(20);
    printf("running...\n");
    printf("running...\n");
}

int main()
{
    print();
    return 10;
}