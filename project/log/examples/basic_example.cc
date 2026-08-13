#include "logsys/mlog.h"

void test_log(const std::string &name)
{
    LOGSYS_INFO("%s", "测试开始");

    logsys::Logger::ptr logger = logsys::LoggerManager::getInstance().getLogger(name);

    LOGSYS_LOGGER_DEBUG(logger, "%s", "测试日志");
    LOGSYS_LOGGER_INFO(logger, "%s", "测试日志");
    LOGSYS_LOGGER_WARN(logger, "%s", "测试日志");
    LOGSYS_LOGGER_ERROR(logger, "%s", "测试日志");
    LOGSYS_LOGGER_FATAL(logger, "%s", "测试日志");

    LOGSYS_INFO("%s", "测试完毕");
}

int main()
{
    std::unique_ptr<logsys::LoggerBuilder> builder(new logsys::GlobalLoggerBuilder());
    builder->buildLoggerName("async_logger");
    builder->buildLoggerLevel(logsys::LogLevel::value::DEBUG);
    builder->buildFormatter("[%c][%f:%l][%p]%m%n");
    builder->buildLoggerType(logsys::LoggerType::LOGGER_SYNC);
    builder->buildSink<logsys::FileSink>("./logfile/sync.log");
    builder->buildSink<logsys::RollBySizeSink>("./logfile/roll-sync-by-size", 1024 * 1024);
    builder->build();

    test_log("async_logger");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}