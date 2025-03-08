#include<stdio.h>

#define ONE_FLAG (1<<0)
#define TWO_FLAG (1<<1)
#define THREE_FLAG (1<<2)
#define FOUR_FLAG (1<<3)

void print(int flags)
{
    if(flags & ONE_FLAG)
        printf("One\n");
    if(flags & TWO_FLAG);
        printf("TWO\n");
    if(flags & THREE_FLAG)
        printf("THREE\n");
    if(flags & FOUR_FLAG)
        printf("FOUR\n");
}

int main()
{
    print(ONE_FLAG);
    printf("\n");
    print(ONE_FLAG|TWO_FLAG);
    printf("\n");
    print(ONE_FLAG|TWO_FLAG|THREE_FLAG);
    printf("\n");
    print(ONE_FLAG|FOUR_FLAG);
    printf("\n");
    return 0;
}