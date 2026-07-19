#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define COMMAND_SIZE 1024
#define FORMAT "%s@%s:%s $ "

#define MAXARGC 128
char *g_argv[MAXARGC];
int g_argc = 0;

const char *GetUserName() {
  const char *name = getenv("USER");
  return name == NULL ? "None" : name;
}

const char *GetHostName() {
  const char *hostname = getenv("HOSTNAME");
  return hostname == NULL ? "None" : hostname;
}

const char *GetPwd() {
  const char *pwd = getenv("PWD");
  return pwd == NULL ? "None" : pwd;
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
  snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetHostName(),
           DirName(GetPwd()).c_str());
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
  while ((bool)(g_argv[g_argc++] = strtok(nullptr, SEP)))
    ;
  return true;
}

void PrintArgv() {
  for (int i = 0; g_argv[i]; i++) {
    printf("argv[%d]->%s\n", i, g_argv[i]);
  }
  printf("argc: %d\n", g_argc);
}

int EXecute() {

  pid_t id = fork();
  if (id == 0) {
    execvp(g_argv[0], g_argv);
    exit(1);
  }

  pid_t rid = waitpid(id, nullptr, 0);
  (void)rid;

  return 0;
}

int main() {
  while (true) {
    // 1. 输出命令行提示符
    PrintCommandPrompt();

    // 2. 获取用户输入的命令
    char commandline[COMMAND_SIZE];
    if (!GetCommandLine(commandline, sizeof(commandline))) {
      continue;
    }

    // 3. 解析命令行
    CommandParse(commandline);
    // PrintArgv();

    // 4. 执行命令
    EXecute();
  }
  return 0;
}
