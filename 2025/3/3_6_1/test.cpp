#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <unordered_map>

#define COMMAND_SIZE 1024
#define FORMAT "[%s@%s %s]# "

// ������shell�����ȫ������

// 1. �����в�����
#define MAXARGC 128
char *g_argv[MAXARGC];
int g_argc = 0; 

// 2. ����������
#define MAX_ENVS 100
char *g_env[MAX_ENVS];
int g_envs = 0;

// 3. ����ӳ���
std::unordered_map<std::string, std::string> alias_list;

// for test
char cwd[4096];
char cwdenv[4096];

// last exit code
int lastcode = 0;

const char *GetUserName()
{
    const char *name = getenv("USER");
    return name == NULL ? "None" : name;
}

const char *GetHostName()
{
    const char *hostname = getenv("HOSTNAME");
    return hostname == NULL ? "None" : hostname;
}

const char *GetPwd()
{
    //const char *pwd = getenv("PWD");
    const char *pwd = getcwd(cwd, sizeof(cwd));
    if(pwd != NULL)
    {
        snprintf(cwdenv, sizeof(cwdenv), "PWD=%s", cwd);
        putenv(cwdenv);
    }
    return pwd == NULL ? "None" : pwd;
}

const char *GetHome()
{
    const char *home = getenv("HOME");
    return home == NULL ? "" : home;
}

void InitEnv()
{
    extern char **environ;
    memset(g_env, 0, sizeof(g_env));
    g_envs = 0;

    //����Ҫ�������ļ���
    //1. ��ȡ��������
    for(int i = 0; environ[i]; i++)
    {
        // 1.1 ����ռ�
        g_env[i] = (char*)malloc(strlen(environ[i])+1);
        strcpy(g_env[i], environ[i]);
        g_envs++;
    }
    g_env[g_envs++] = (char*)"HAHA=for_test"; //for_test
    g_env[g_envs] = NULL;

    //2. ���ɻ�������
    for(int i = 0; g_env[i]; i++)
    {
        putenv(g_env[i]);
    }
    environ = g_env;
}

//command
bool Cd()
{
    // cd argc = 1
    if(g_argc == 1)
    {
        std::string home = GetHome();
        if(home.empty()) return true;
        chdir(home.c_str());
    }
    else
    {
        std::string where = g_argv[1];
        // cd - / cd ~
        if(where == "-")
        {
            // Todu
        }
        else if(where == "~")
        {
            // Todu
        }
        else
        {
            chdir(where.c_str());
        }
    }
    return true;
}

void Echo()
{
    if(g_argc == 2)
    {
        // echo "hello world"
        // echo $?
        // echo $PATH
        std::string opt = g_argv[1];
        if(opt == "$?")
        {
            std::cout << lastcode << std::endl;
            lastcode = 0;
        }
        else if(opt[0] == '$')
        {
            std::string env_name = opt.substr(1);
            const char *env_value = getenv(env_name.c_str());
            if(env_value)
                std::cout << env_value << std::endl;
        }
        else
        {
            std::cout << opt << std::endl;
        }
    }
}

// / /a/b/c
std::string DirName(const char *pwd)
{
#define SLASH "/"
    std::string dir = pwd;
    if(dir == SLASH) return SLASH;
    auto pos = dir.rfind(SLASH);
    if(pos == std::string::npos) return "BUG?";
    return dir.substr(pos+1);
}

void MakeCommandLine(char cmd_prompt[], int size)
{
    snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetHostName(), DirName(GetPwd()).c_str());
    //snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetHostName(), GetPwd());
}

void PrintCommandPrompt()
{
    char prompt[COMMAND_SIZE];
    MakeCommandLine(prompt, sizeof(prompt));
    printf("%s", prompt);
    fflush(stdout);
}

bool GetCommandLine(char *out, int size)
{
    // ls -a -l => "ls -a -l\n" �ַ���
    char *c = fgets(out, size, stdin);
    if(c == NULL) return false;
    out[strlen(out)-1] = 0; // ����\n
    if(strlen(out) == 0) return false;
    return true;
}

// 3. �����з��� "ls -a -l" -> "ls" "-a" "-l"
bool CommandParse(char *commandline)
{
#define SEP " "
    g_argc = 0;
    // �����з��� "ls -a -l" -> "ls" "-a" "-l"
    g_argv[g_argc++] = strtok(commandline, SEP);
    while((bool)(g_argv[g_argc++] = strtok(nullptr, SEP)));
    g_argc--;
    return g_argc > 0 ? true:false;
}

void PrintArgv()
{
    for(int i = 0; g_argv[i]; i++)
    {
        printf("argv[%d]->%s\n", i, g_argv[i]);
    }
    printf("argc: %d\n", g_argc);
}

bool CheckAndExecBuiltin()
{
    std::string cmd = g_argv[0];
    if(cmd == "cd")
    {
        Cd();
        return true;
    }
    else if(cmd == "echo")
    {
        Echo();
        return true;
    }
    else if(cmd == "export")
    {
    }
    else if(cmd == "alias")
    {
       // std::string nickname = g_argv[1];
       // alias_list.insert(k, v);
    }

    return false;
}

int Execute()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child
        execvp(g_argv[0], g_argv);
        exit(1);
    }
    int status = 0;
    // father
    pid_t rid = waitpid(id, &status, 0);
    if(rid > 0)
    {
        lastcode = WEXITSTATUS(status);
    }
    return 0;
}

int main()
{
    // shell ������ʱ�򣬴�ϵͳ�л�ȡ��������
    // ���ǵĻ���������ϢӦ�ôӸ�shellͳһ��
    InitEnv();

    while(true)
    {
        // 1. �����������ʾ��
        PrintCommandPrompt();

        // 2. ��ȡ�û����������
        char commandline[COMMAND_SIZE];
        if(!GetCommandLine(commandline, sizeof(commandline)))
            continue;

        // 3. �����з��� "ls -a -l" -> "ls" "-a" "-l"
        if(!CommandParse(commandline))
            continue;
        //PrintArgv();

        // ������
        // 4. ��Ⲣ�����ڼ�����
        if(CheckAndExecBuiltin())
            continue;

        // 5. ִ������
        Execute();
    }
    //cleanup();
    return 0;
}