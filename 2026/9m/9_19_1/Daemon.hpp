#pragma once

#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Common.hpp"
#include "Log.hpp"

const std::string dev = "/dev/null";

using namespace LogModule;

void Daemon(int nochdir, int noclose)
{
    // 1. 忽略IO，子进程退出等相关信号
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);

    // 2. 父进程直接结束
    if (fork() > 0)
        exit(0);

    // 3. 只能是子进程且父进程为1
    setsid(); // 成为独立会话

    if (nochdir == 0)
        chdir("/");

    // 4. 守护进程，关闭0，1，2，或打开dev/null，重定向IO以及err流
    if (noclose == 0)
    {
        int fd = ::open(dev.c_str(), O_RDWR);
        if (fd < 0)
        {
            LOG(LogLevel::FATAL) << "open" << dev << "errno";
            exit(OPEN_ERR);
        }
        else
        {
            dup2(fd, 0);
            dup2(fd, 1);
            dup2(fd, 2);
            close(fd);
        }
    }
}
