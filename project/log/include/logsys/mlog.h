#ifndef LOGSYS_MLOG_H
#define LOGSYS_MLOG_H

#include "logger.hpp"

namespace logsys
{
    inline Logger::ptr getLogger(const std::string &name)
    {
        return LoggerManager::getInstance().getLogger(name);
    }

    inline Logger::ptr rootLogger()
    {
        return LoggerManager::getInstance().rootLogger();
    }
}

// 默认 root logger 日志宏
#define LOGSYS_DEBUG(fmt, ...) logsys::rootLogger()->debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSYS_INFO(fmt, ...) logsys::rootLogger()->info(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSYS_WARN(fmt, ...) logsys::rootLogger()->warn(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSYS_ERROR(fmt, ...) logsys::rootLogger()->error(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSYS_FATAL(fmt, ...) logsys::rootLogger()->fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

// 指定 logger 的日志宏
#define LOGSYS_LOGGER_DEBUG(logger, fmt, ...) (logger)->debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSYS_LOGGER_INFO(logger, fmt, ...) (logger)->info(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSYS_LOGGER_WARN(logger, fmt, ...) (logger)->warn(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSYS_LOGGER_ERROR(logger, fmt, ...) (logger)->error(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSYS_LOGGER_FATAL(logger, fmt, ...) (logger)->fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

// 兼容旧接口：不推荐新代码继续使用
#ifndef LOGSYS_DISABLE_SHORT_MACROS
#define DEBUG(fmt, ...) LOGSYS_DEBUG(fmt, ##__VA_ARGS__)
#define INFO(fmt, ...) LOGSYS_INFO(fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) LOGSYS_WARN(fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...) LOGSYS_ERROR(fmt, ##__VA_ARGS__)
#define FATAL(fmt, ...) LOGSYS_FATAL(fmt, ##__VA_ARGS__)
#endif

#endif