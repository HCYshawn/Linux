#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("Before execl\n");

    execl("/bin/ls","ls","-l",NULL);
    printf("This will not be printed if execl is successful.\n");
    return 0;
}