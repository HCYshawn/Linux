#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//char *newnew = (char*)"myVAL=66666666";
char *const addenv[] = {
    (char *const)"MYVAL=123456789",
    (char *const)"MYVAL1=123456789",
    (char *const)"MYVAL2=123456789",
    NULL
};

int main()
{
    printf("我的程序要运行了!\n");

    if(fork() == 0)
    {
        printf("I am Child, My Pid Is: %d\n", getpid());
        sleep(1);

        char *const argv[] = {
            (char*const)"other",
            (char*const)"-a",
            (char*const)"-b",
            (char*const)"-c",
            (char*const)"-d",
            NULL
        };

        for(int i = 0; addenv[i]; i++)
        {
            putenv(addenv[i]);
        }
        extern char **environ;
        execvpe("./other", argv, environ);
        
        //putenv(newnew);

        //execvp("./other", argv);
        //execv("/usr/bin/ls", argv);

        //execlp("/usr/bin/ls", "ls", "-ln", "-a", NULL);
        //child
        //execl("/usr/bin/ls", "/usr/bin/ls", "-ln", "-a", NULL);
        //execl("./other", "other", NULL);
        //execl("/usr/bin/python3", "python", "other.py", NULL);
        //execl("/usr/bin/bash", "bash", "other.sh", NULL);
        exit(1);
    }

    waitpid(-1, NULL, 0);
    printf("我的程序运行完毕了\n");
    //return 0;
}
