#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<unordered_map>


#define COMMAND_SIZE 1024
#define FORMAT "%s@%s:%s $ "

//shell自定义的全局数据

//1. 命令行参数表
#define MAXARGC 128
char *g_argv[MAXARGC];
int g_argc = 0;

//2. 环境变量表
#define MAX_ENVS 100
char*g_env[MAX_ENVS];
int g_envs = 0;

//3. 别名映射表
std::unordered_map<std::string,std::string> alias_list;

char cwd[1030];
char cwdenv[1030];

//last exit code 
int lastcode = 0;

const char *GetUserName() {
  const char *name = getenv("USER");
  return name == NULL ? "None" : name;
}

const char *GetHostName() {
  const char *hostname = getenv("HOSTNAME");
  return hostname == NULL ? "None" : hostname;
}

const char *GetPwd() {
  //const char *pwd = getenv("PWD");
  const char* pwd = getcwd(cwd, sizeof(cwd));
    if(pwd == nullptr)
    {
        return "None";
    }

    setenv("PWD", cwd, 1);
    return cwd;
}

const char *GetHome() {
  const char *home = getenv("HOME");
  return home == NULL ? "" : home;
}

void Initenv()
{
    extern char **environ;
    memset(g_env,0,sizeof(g_env));
    g_envs = 0;

    //获取环境变量
    for(int i = 0;environ[i];i++)
    {
        g_env[i] = (char*)malloc(strlen(environ[i])+1);
        strcpy(g_env[i],environ[i]);
        g_envs++;
    }
    g_env[g_envs++] = (char*)"HAHA=for_test";
    g_env[g_envs] = NULL;

    //导成环境变量
    for(int i = 0;g_env[i];i++)
    {
        putenv(g_env[i]); 
    }
    environ = g_env;
}

bool Cd()
{
    if(g_argc == 1)
    {
    std::string home = GetHome();
    if(home.empty())return true;
    chdir(home.c_str());
    }
    else
    {
    std::string where = g_argv[1];
    if(where == "-")
    {

    }
    else if(where == "~")
    {

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
        std::string opt = g_argv[1];
        if(opt == "$?")
        {
            std::cout<<lastcode<<std::endl;
            lastcode = 0;
        }
        else if(opt[0] == '$')
        {
            std::string env_name = opt.substr(1);
            const char* env_value = getenv(env_name.c_str());
            if(env_value)
            {
                std::cout<<env_value<<std::endl;
            }
        }
        else
        {
            std::cout<<opt<<std::endl;
        }
        
    }
}

std::string DirName(const char *pwd) {
#define SLASH "/"

  std::string dir = pwd;
  if (dir == SLASH)
    return SLASH;
  auto pos = dir.rfind(SLASH);
  if (pos == std::string::npos)
    return "BUG?";
  return dir.substr(pos + 1);
}

void MakeCommandLine(char cmd_prompt[], int size) {
  snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetHostName(), DirName(GetPwd()).c_str());
    //snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetHostName(),DirName(GetPwd()).c_str());
}

void PrintCommandPrompt() {
  char prompt[COMMAND_SIZE];
  MakeCommandLine(prompt, sizeof(prompt));
  printf("%s", prompt);
  fflush(stdout);
}

bool GetCommandLine(char *out, int size) {
  char *c = fgets(out, size, stdin);
  if (c == NULL)
    return false;

  out[strlen(out) - 1] = 0; // 清理\n
  if (strlen(out) == 0)
    return false;
  return true;
}

bool CommandParse(char *commandline) {
#define SEP " "
  g_argc = 0;

  g_argv[g_argc++] = strtok(commandline, SEP);
  while ((bool)(g_argv[g_argc++] = strtok(nullptr, SEP)));
  g_argc--;
  return g_argc>0?true:false;
}

void PrintArgv() {
  for (int i = 0; g_argv[i]; i++) {
    printf("argv[%d]->%s\n", i, g_argv[i]);
  }
  printf("argc: %d\n", g_argc);
}

bool CheckAndExecBuiltin()
{
    std::string cmd = g_argv[0];
    if(cmd=="cd")
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
    return false;
}

int EXecute() {

  pid_t id = fork();
  if (id == 0) {
    execvp(g_argv[0], g_argv);
    exit(1);
  }
  int status = 0;
  pid_t rid = waitpid(id, &status, 0);
  if(rid > 0)
  {
    lastcode = WEXITSTATUS(status);
  }

  return 0;
}

int main() {
    //shell启动需要从系统获取环境变量
    Initenv();

  while (true) {
    // 1. 输出命令行提示符
    PrintCommandPrompt();

    // 2. 获取用户输入的命令
    char commandline[COMMAND_SIZE];
    if (!GetCommandLine(commandline, sizeof(commandline))) {
      continue;
    }

    // 3. 解析命令行
    if(!CommandParse(commandline))
        continue;
    // PrintArgv();

    //4. 检测并处理内键命令
    if(CheckAndExecBuiltin())
        continue;

    // 5. 执行命令
    EXecute();
  }
  return 0;
}
