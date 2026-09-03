#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <iostream>
#include <string>
#include <filesystem> //c++17
#include <fstream>
#include "Mutex.hpp"

namespace LogModule
{
    using namespace MutexModule;

    const std::string gsep = "\r\n";

    // 刷新策略，a：显示器打印，b：向指定的文件写入
    // 策略基类
    class LogStrategy
    {
    public:
        ~LogStrategy() = default;
        virtual void SyncLog(const std::string &message) = 0;
    };

    // 显示器打印日志的策略
    class ConsoleLogStrategy : public LogStrategy
    {
    public:
        ConsoleLogStrategy()
        {
        }

        void SyncLog(const std::string &message) override
        {
            LockGuard lockguard(_mutex);
            std::cout << message << gsep;
        }

        ~ConsoleLogStrategy()
        {
        }

    private:
        Mutex _mutex;
    };

    // 缺省路径以及文件
    const std::string defaultpath = "./log";
    const std::string defaultfile = "my.log";

    // 文件打印日志的策略
    class FileLogStrategy : public LogStrategy
    {
    public:
        FileLogStrategy(const std::string &path = defaultpath, const std::string &file = defaultfile)
            : _path(path),
              _file(file)
        {
            LockGuard lockguard(_mutex);
            if (std::filesystem::exists(_path))
            {
                return;
            }
            try
            {
                std::filesystem::create_directories(_path);
            }
            catch (const std::filesystem::filesystem_error &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        void SyncLog(const std::string &message) override
        {
            LockGuard lockguard(_mutex);
            std::string filename = _path + (_path.back() == '/' ? "" : "/") + _file;
            std::ofstream out(filename, std::ios::app); // 追加打开
            if (!out.is_open())
            {
                return;
            }

            out << message << gsep;
            out.close();
        }

        ~FileLogStrategy()
        {
        }

    private:
        std::string _path;
        std::string _file;

        Mutex _mutex;
    };
}

#endif