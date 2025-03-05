#include<stdio.h>
#include<unistd.h>

int main()
{
    char *args[] = {"ls","-l",NULL};
    char *env[] = {"PATH=/bin",NULL};
    printf("Before execve\n");

    if(execve("/bin/ls",args,env) == -1)
    {
        perror("execve failed");
    }
    printf("This will not be printed if execve is successful\n");
    return 0;
}