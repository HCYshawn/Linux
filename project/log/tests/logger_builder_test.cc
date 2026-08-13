#include "logsys/mlog.h"

void test_log()
{
    // logsys::Logger::ptr logger = logsys::LoggerManager::getInstance().getLogger("async_logger");
    // logger->debug("%s", "测试日志");
    // logger->info("%s", "测试日志");
    // logger->warn("%s", "测试日志");
    // logger->error("%s", "测试日志");
    // logger->fatal("%s", "测试日志");

    // size_t count = 0;
    // while (count < 500000)
    // {
    //     logger->fatal("测试日志-%d", count++);
    // }
    LOGSYS_DEBUG("%s", "测试日志");
    LOGSYS_INFO("%s", "测试日志");
    LOGSYS_WARN("%s", "测试日志");
    LOGSYS_ERROR("%s", "测试日志");
    LOGSYS_FATAL("%s", "测试日志");

    size_t count = 0;
    while (count < 500000)
    {
        LOGSYS_FATAL("测试日志-%d", count++);
    }
}

int main()
{
    // std::ifstream ifs("./logfile/test.log", std::ios::binary);
    // if (ifs.is_open() == false)
    // {
    //     std::cout << "open faild!\n";
    //     return -1;
    // }
    // ifs.seekg(0, std::ios::end);
    // size_t fsize = ifs.tellg();
    // ifs.seekg(0, std::ios::beg);
    // std::string body;
    // body.resize(fsize);
    // ifs.read(&body[0], fsize);
    // if (ifs.good() == false)
    // {
    //     std::cout << "read error\n";
    //     return -1;
    // }
    // ifs.close();

    // std::cout << fsize << std::endl;
    // logsys::Buffer buffer;
    // for (int i = 0; i < body.size(); i++)
    // {
    //     buffer.push(&body[i], 1);
    // }

    // std::cout << buffer.readAbleSize() << std::endl;

    // std::ofstream ofs("./logfile/tmp.log", std::ios::binary);
    // size_t rsize = buffer.readAbleSize();
    // for (int i = 0; i < rsize; i++)
    // {
    //     ofs.write(buffer.begin(), 1);
    //     if (ofs.good() == false)
    //     {
    //         std::cout << "write error!\n";
    //         return -1;
    //     }
    //     buffer.moveReader(1);
    // }
    // ofs.close();
    // std::string logger_name = "sync_logger";
    // logsys::LogLevel::value limit = logsys::LogLevel::value::WARN;
    // logsys::Formatter::ptr fmt(new logsys::Formatter("[%d{%H:%M:%S}][%c][%f:%l][%p]%T%m%n"));

    // logsys::LogSink::ptr stdout_lsp = logsys::SinkFactory::create<logsys::StdoutSink>();
    // logsys::LogSink::ptr file_lsp = logsys::SinkFactory::create<logsys::FileSink>("./logfile/test.log");
    // logsys::LogSink::ptr roll_lsp = logsys::SinkFactory::create<logsys::RollBySizeSink>("./logfile/roll-", 1024 * 1024);

    // std::vector<logsys::LogSink::ptr> sinks = {stdout_lsp, file_lsp, roll_lsp};
    // logsys::Logger::ptr logger(new logsys::SyncLogger(logger_name, limit, fmt, sinks));

    std::unique_ptr<logsys::LoggerBuilder> builder(new logsys::GlobalLoggerBuilder());
    builder->buildLoggerName("async_logger");
    builder->buildLoggerLevel(logsys::LogLevel::value::WARN);
    builder->buildFormmatter("[%c][%f:%l]%m%n");
    builder->buildLoggerType(logsys::LoggerType::LOGGER_ASYNC);
    builder->buildEnableUnSafeAsync();
    builder->buildSink<logsys::FileSink>("./logfile/async.log");
    builder->buildSink<logsys::StdoutSink>();
    builder->build();

    test_log();
    // builder->buildSink<logsys::RollBySizeSink>("./logfile/roll-", 1024 * 1024);

    // logsys::LogMsg msg(logsys::LogLevel::value::INFO,53,"main.c","root","格式化测试...");
    // //logsys::Formatter fmt("abc%%abc%g%g%g[%d{%H:%M:%S}] %m%n%g");
    // logsys::Formatter fmt;
    // std::string str  = fmt.format(msg);
    // std::cout<<str<<std::endl;
    // logsys::LogSink::ptr stdout_lsp = logsys::SinkFactory::create<logsys::StdoutSink>();
    // logsys::LogSink::ptr file_lsp = logsys::SinkFactory::create<logsys::FileSink>("./logfile/test.log");
    // logsys::LogSink::ptr roll_lsp = logsys::SinkFactory::create<logsys::RollBySizeSink>("./logfile/roll-",1024*1024);
    // stdout_lsp->log(str.c_str(),str.size());
    // file_lsp->log(str.c_str(),str.size());
    // size_t cursize = 0;
    // size_t count = 0;
    // while(cursize<1024*1024*10)
    // {
    //     std::string tmp = str+std::to_string(count++);
    //     roll_lsp->log(str.c_str(),str.size());
    //     cursize += tmp.size();
    // }
    // std::cout<<logsys::LogLevel::toString(logsys::LogLevel::value::DEBUG)<<std::endl;
    // std::cout<<logsys::LogLevel::toString(logsys::LogLevel::value::INFO)<<std::endl;
    // std::cout<<logsys::LogLevel::toString(logsys::LogLevel::value::WARN)<<std::endl;
    // std::cout<<logsys::LogLevel::toString(logsys::LogLevel::value::ERROR)<<std::endl;
    // std::cout<<logsys::LogLevel::toString(logsys::LogLevel::value::FATAL)<<std::endl;
    // std::cout<<logsys::LogLevel::toString(logsys::LogLevel::value::OFF)<<std::endl;
    // std::cout<<logsys::util::date::now()<<std::endl;
    // std::string path = "./abc/bcd/a.txt";
    // logsys::util::file::create_directory(logsys::util::file::path(path));
    return 0;
}