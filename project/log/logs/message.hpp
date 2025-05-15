/*
    定义日志消息类，进行日志中间信息的存储：
    1. 日志的输出时间    用于过滤日志输出时间
    2. 日志等级         用于进行日志过滤分析
    3. 源文件名称       
    4. 源文件行号        用于定位出现错误的代码位置
    5. 线程ID           用于过滤出错的线程
    6. 日志主体消息
    7. 日志器名称       (当前支持多日志器的同时使用)
*/

#include "level.hpp"
#include<isotream>
#include<string>
#include<thread>


namespace bitlog
{
    struct LogMsg
    {
        size_t ctime;
        LogLevel::value level;
        size_t _line;
        std::thread::id _tid;
        std::string _file;
        std::string _logger;
        std::string _payload;

        LogMsg(LogLevel::value _level,
            size_t _line,
            const std::string& _file,
            const std::string& _logger,
            const std::string& _payload)
            : ctime(util::Date::now()), 
            level(level), 
            line(line), 
            _tid(std::this_thread::get_id()), 
            file(file), 
            _logger(logger), 
            _payload(payload) {}
    }
}