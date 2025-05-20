/*
    日志器模块：
    1. 抽象日志器基类
    2. 派生出不同的子类（同步日志器类 与 异步日志器类）
*/
#ifndef __M_LOGGER_H__
#define __M_LOGGER_H__

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "util.hpp"
#include "level.hpp"
#include "format.hpp"
#include "sink.hpp"
#include <atomic>
#include <cstdarg>
#include <mutex>
#include <sstream>

namespace bitlog
{
    class Logger
    {
    public:
        using ptr = std::shared_ptr<Logger>;
        Logger(const std::string &logger_name,
               LogLevel::value level,
               Formatter::ptr &formatter,
               std::vector<LogSink::ptr> &sinks) : _logger_name(logger_name),
                                                   _limit_level(level),
                                                   _formatter(formatter),
                                                   _sinks(sinks.begin(), sinks.end()) {}

        // 完成构造日志消息对象过程并进行格式化，得到格式化后的日志消息字符串然后进行落地输出
        void debug(const std::string &file, size_t line, const std::string &fmt, ...)
        {
            // 1. 判断当前的日志是否达到了输出等级
            if (LogLevel::value::DEBUG < _limit_level)
            {
                return;
            }

            // 2. 对fmt格式化字符串和不定参进行字符串组织，得到的日志消息的字符串
            va_list ap;
            va_start(ap, fmt);
            char *res;
            int ret = vasprintf(&res, fmt.c_str(), ap);
            if (ret == -1)
            {
                std::cout << "vasprintf failed!\n";
                return;
            }
            va_end(ap);

            serialize(LogLevel::value::DEBUG, file, line, res);
            free(res);
        }

        void info(const std::string &file, size_t line, const std::string &fmt, ...)
        {
            // 1. 判断当前的日志是否达到了输出等级
            if (LogLevel::value::INFO < _limit_level)
            {
                return;
            }

            // 2. 对fmt格式化字符串和不定参进行字符串组织，得到的日志消息的字符串
            va_list ap;
            va_start(ap, fmt);
            char *res;
            int ret = vasprintf(&res, fmt.c_str(), ap);
            if (ret == -1)
            {
                std::cout << "vasprintf failed!\n";
                return;
            }
            va_end(ap);

            serialize(LogLevel::value::INFO, file, line, res);
            free(res);
        }

        void warn(const std::string &file, size_t line, const std::string &fmt, ...)
        {
            // 1. 判断当前的日志是否达到了输出等级
            if (LogLevel::value::WARN < _limit_level)
            {
                return;
            }

            // 2. 对fmt格式化字符串和不定参进行字符串组织，得到的日志消息的字符串
            va_list ap;
            va_start(ap, fmt);
            char *res;
            int ret = vasprintf(&res, fmt.c_str(), ap);
            if (ret == -1)
            {
                std::cout << "vasprintf failed!\n";
                return;
            }
            va_end(ap);

            serialize(LogLevel::value::WARN, file, line, res);
            free(res);
        }

        void error(const std::string &file, size_t line, const std::string &fmt, ...)
        {
            // 1. 判断当前的日志是否达到了输出等级
            if (LogLevel::value::ERROR < _limit_level)
            {
                return;
            }

            // 2. 对fmt格式化字符串和不定参进行字符串组织，得到的日志消息的字符串
            va_list ap;
            va_start(ap, fmt);
            char *res;
            int ret = vasprintf(&res, fmt.c_str(), ap);
            if (ret == -1)
            {
                std::cout << "vasprintf failed!\n";
                return;
            }
            va_end(ap);

            serialize(LogLevel::value::ERROR, file, line, res);
            free(res);
        }

        void fatal(const std::string &file, size_t line, const std::string &fmt, ...)
        {
            // 1. 判断当前的日志是否达到了输出等级
            if (LogLevel::value::FATAL < _limit_level)
            {
                return;
            }

            // 2. 对fmt格式化字符串和不定参进行字符串组织，得到的日志消息的字符串
            va_list ap;
            va_start(ap, fmt);
            char *res;
            int ret = vasprintf(&res, fmt.c_str(), ap);
            if (ret == -1)
            {
                std::cout << "vasprintf failed!\n";
                return;
            }
            va_end(ap);

            serialize(LogLevel::value::FATAL, file, line, res);
            free(res);
        }

    protected:
        void serialize(LogLevel::value level, const std::string &file, size_t line, char *str)
        {
            // 3. 构造LogMsg对象
            LogMsg msg(level, line, file, _logger_name, str);

            // 4. 通过格式化工具对LogMsg进行格式化，得到格式化后的日志字符串
            std::stringstream ss;
            _formatter->format(ss, msg);
            // 5. 进行日志落地
            log(ss.str().c_str(), ss.str().size());
        }
        virtual void log(const char *data, size_t len) = 0;

    protected:
        std::mutex _mutex;
        std::string _logger_name;
        std::atomic<LogLevel::value> _limit_level;
        Formatter::ptr _formatter;
        std::vector<LogSink::ptr> _sinks;
    };

    class SyncLogger : public Logger
    {
    public:
        SyncLogger(const std::string &logger_name,
                   LogLevel::value level,
                   Formatter::ptr &formatter,
                   std::vector<LogSink::ptr> &sinks) : Logger(logger_name, level, formatter, sinks) {}

    protected:
        void log(const char *data, size_t len)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            if (_sinks.empty())
                return;
            for (auto &sink : _sinks)
            {
                sink->log(data, len);
            }
        }
    };

    enum class LoggerType
    {
        LOGGER_SYNC,
        LOGGER_ASYNC
    };

    // 抽象一个日志器建造者类（完成日志器对象对所需零部件的构建和日志器的构建
    // 1. 设置日志器类型
    // 2. 将不同类型的日志器的创建放到同一个日志器建造者类中完成
    class LoggerBuilder
    {
    public:
        LoggerBuilder() : _logger_type(LoggerType::LOGGER_SYNC),
                          _limit_level(LogLevel::value::DEBUG)
        {
        }
        void buildLoggerType(LoggerType type)
        {
            _logger_type = type;
        }

        void buildLoggerName(const std::string &name)
        {
            _logger_name = name;
        }

        void buildLoggerLevel(LogLevel::value level)
        {
            _limit_level = level;
        }

        void buildFormmatter(const std::string &pattern)
        {
            _formatter = std::make_shared<Formatter>(pattern);
        }

        template <typename SinkType, typename... Args>
        void buildSink(Args &&...args)
        {
            LogSink::ptr psink = SinkFactory::create<SinkType>(std::forward<Args>(args)...);
            _sinks.push_back(psink);
        }

        virtual Logger::ptr build() = 0;

    protected:
        LoggerType _logger_type;
        std::string _logger_name;
        std::atomic<LogLevel::value> _limit_level;
        Formatter::ptr _formatter;
        std::vector<LogSink::ptr> _sinks;
    };

    class LocalLoggerBuilder : public LoggerBuilder
    {
    public:
        Logger::ptr build() override
        {
            assert(!_logger_name.empty());
            if (_formatter.get() == nullptr)
            {
                _formatter = std::make_shared<Formatter>();
            }
            if (_sinks.empty())
            {
                buildSink<StdoutSink>();
            }
            if (_logger_type == LoggerType::LOGGER_ASYNC)
            {
            }
            return std::make_shared<SyncLogger>(_logger_name, _limit_level, _formatter, _sinks);
        }
    };
}

#endif