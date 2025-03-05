#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define COMMAND_SIZE 1024
#define FORMAT "[%s@%s %s]$ "

#define MAX_ARGC 128
char *g_argv[MAX_ARGC];
int g_argc = 0;

const char *GetUserName()
{
    const char *name = getenv("USER");
    return name == NULL ? "Noene" : name;
}

const char *GetHostName()
{
    const char *hostname = getenv("HOSTNAME");
    return hostname == NULL ? "None" : hostname;
}

const char *GetPwd()
{
    const char *pwd = getenv("PWD");
    //const char *pwd = getcwd(cwd,sizeof(cwd));
    // if(pwd != NULL)
    // {
    //     snprintf(cwdenv,sizeof(cwdenv),"PWD=%s",cwd);
    //     putenv(cwdenv);
    // }
    return pwd == NULL ? "None" : pwd;
}
// const char *GetHome()
// {
//     const char *home = getenv("HOME");
//     return home == NULL ? "" : home;
// }

std::string DirName(const char *pwd)
{
#define SLASH "/"
    std::string dir = pwd;
    if(dir == SLASH) return SLASH;
    auto pos = dir.rfind(SLASH);
    if(pos == std::string::npos) return "BUG?";
    return dir.substr(pos+1);
}

void MakeCommandLine(char cmd_prompt[],int size)
{
    snprintf(cmd_prompt,size,FORMAT,GetUserName(),GetHostName(),DirName(GetPwd()).c_str());
}

void PrintCommmandPrompt()
{
    char prompt[COMMAND_SIZE];
    MakeCommandLine(prompt,sizeof(prompt));
    printf("%s",prompt);
    fflush(stdout);
}

bool GetCommandLine(char *out,int size)
{
    char *c = fgets(out,size,stdin);
    if(c == NULL) return false;
    out[strlen(out)-1] = 0;
    if(strlen(out) == 0) return false;
    return true;
}

bool CommandParse(char *commandline)
{
#define SEP " "
    g_argc = 0;
    g_argv[g_argc++] = strtok(commandline,SEP);
    while((bool)(g_argv[g_argc++] == strtok(nullptr,SEP)));
    g_argc--;
    return true;    
}

void PrintArgv()
{
    for(int i = 0;g_argv[i];i++)
    {
        printf("argv[%d]->%s\n",i,g_argv[i]);
    }
    printf("argc: %d\n",g_argc);
}

int Execute()
{
    pid_t id = fork();
    if(id == 0)
    {
        execvp(g_argv[0],g_argv);
        exit(1);
    }
    pid_t rid = waitpid(id,nullptr,0);
    (void)rid;
    return 0;
}

int main()
{
    while(true)
    {
        PrintCommmandPrompt();

        char commandline[COMMAND_SIZE];
        if(!GetCommandLine(commandline,sizeof(commandline)))
            continue;

        CommandParse(commandline);
        Execute();
    }
    
    return 0;
}