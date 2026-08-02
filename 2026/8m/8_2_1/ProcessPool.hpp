#ifndef __PROCESS_POOL_HPP__
#define __PROCESS_POOL_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include "Task.hpp"
#include <sys/wait.h>

class Channel
{
public:
    Channel(int fd, pid_t id) : _wfd(fd), _subid(id)
    {
        _name = "channel-" + std::to_string(_wfd) + "-" + std::to_string(_subid);
    }

    ~Channel() {}

    void Send(int code)
    {
        int n = write(_wfd, &code, sizeof(code));
        (void)n;
    }

    void Wait()
    {
        pid_t rid = waitpid(_subid, nullptr, 0);
        (void)rid;
    }

    void Close()
    {
        close(_wfd);
    }

    int Fd()
    {
        return _wfd;
    }

    pid_t SubId()
    {
        return _subid;
    }

    std::string Name()
    {
        return _name;
    }

private:
    int _wfd;
    pid_t _subid;
    std::string _name;
};

class ChannelManager
{
public:
    ChannelManager() : _next(0)
    {
    }

    void Insert(int wfd, pid_t subid)
    {
        _channels.emplace_back(wfd, subid);
        // Channel c(wfd, subid);
        //_channels.push_back(c);
    }

    Channel &Select()
    {
        auto &c = _channels[_next];
        _next++;
        _next %= _channels.size();
        return c;
    }

    void PrintChannel()
    {
        for (auto &channel : _channels)
        {
            std::cout << channel.Name() << std::endl;
        }
    }

    void CloseAll()
    {
        for (auto &channel : _channels)
        {
            channel.Close();
        }
    }

    void StopSubProess()
    {
        for (auto &channel : _channels)
        {
            channel.Close();
            std::cout << "关闭: " << channel.Name() << std::endl;
        }
    }

    void WaitSubProcess()
    {
        for (auto &channel : _channels)
        {
            channel.Wait();
            std::cout << "回收: " << channel.Name() << std::endl;
        }
    }

    ~ChannelManager() {}

private:
    std::vector<Channel> _channels;
    int _next;
};

const int gdefaultnum = 5;

class ProcessPool
{
public:
    ProcessPool(int num) : _process_num(num)
    {
        _tm.Resister(PrintLog);
        _tm.Resister(Download);
        _tm.Resister(Upload);
    }

    void Work(int rfd)
    {
        while (true)
        {
            // std::cout << "I am child, my rfd: " << std::endl;
            // sleep(1);

            int code = 0;
            ssize_t n = read(rfd, &code, sizeof(code));
            if (n > 0)
            {
                if (n != sizeof(code))
                {
                    continue;
                }
                std::cout << "child [ " << getpid() << " ] receives the task code" << std::endl;
                _tm.Execute(code);
            }
            else if (n == 0)
            {
                std::cout << "child exit..." << std::endl;
                break;
            }
            else
            {
                std::cout << "read fail..." << std::endl;
                break;
            }
        }
    }

    bool Start()
    {
        for (int i = 0; i < _process_num; i++)
        {
            // 1. 创建管道
            int pipefd[2] = {0};
            int n = pipe(pipefd);
            if (n < 0)
            {
                return 0;
            }

            // 2. 创建子进程
            pid_t subid = fork();
            if (subid < 0)
                return false;
            else if (subid == 0)
            {
                // 子进程
                //关闭继承的其他管道
                _cm.CloseAll();

                // 3. 关闭不需要的文件描述符
                close(pipefd[1]);

                Work(pipefd[0]);
                close(pipefd[0]);
                exit(0);
            }
            else
            {
                // 父进程
                // 3. 关闭不需要的文件描述符
                close(pipefd[0]);

                _cm.Insert(pipefd[1], subid);
            }
        }
        return true;
    }

    void Debug()
    {
        _cm.PrintChannel();
    }

    void Run()
    {
        // 1. 选择一个任务
        int taskcode = _tm.Code();

        // 2. 负载均衡选择信道，轮询
        auto &c = _cm.Select();
        std::cout << "select child: " << c.Name() << std::endl;

        // 3. 发送任务
        c.Send(taskcode);
        std::cout << "Send task code: " << taskcode << std::endl;
    }

    void Stop()
    {
        // 关闭父进程所有的wfd即可
        _cm.StopSubProess();

        // 回收所有子进程
        _cm.WaitSubProcess();
    }

    ~ProcessPool()
    {
    }

private:
    ChannelManager _cm;
    int _process_num;
    TaskManager _tm;
};

#endif