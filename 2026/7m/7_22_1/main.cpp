#include<iostream>
#include<cstdio>

#define ONE_FLAG (1<<0)
#define TWO_FLAG (1<<1)
#define THREE_FLAG (1<<2)
#define FOUR_FLAG (1<<3)

void Print(int flags)
{
    if(flags & ONE_FLAG)
        printf("One!\n");
    if(flags & TWO_FLAG)
        printf("Two!\n");
    if(flags & THREE_FLAG)
        printf("Three!\n");
    if(flags & FOUR_FLAG)
        printf("Four!\n");
}


int main()
{
    Print(ONE_FLAG);
    printf("\n");
    Print(ONE_FLAG | TWO_FLAG);
    printf("\n");
    Print(ONE_FLAG|TWO_FLAG|THREE_FLAG);
    printf("\n");
    Print(ONE_FLAG|TWO_FLAG|THREE_FLAG|FOUR_FLAG);
    printf("\n");
    Print(ONE_FLAG|FOUR_FLAG);
    printf("\n");
    return 0;
}
