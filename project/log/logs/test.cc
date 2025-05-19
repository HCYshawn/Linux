#include"util.hpp"
#include"level.hpp"
#include"message.hpp"
#include"format.hpp"
#include"sink.hpp"
#include"logger.hpp"

int main()
{
    std::string logger_name = "sync_logger";
    bitlog::LogLevel::value limit = bitlog::LogLevel::value::WARN;
    bitlog::Formatter::ptr fmt(new bitlog::Formatter("[%d{%H:%M:%S}][%c][%f:%l][%p]%T%m%n"));

    bitlog::LogSink::ptr stdout_lsp = bitlog::SinkFactory::create<bitlog::StdoutSink>();
    bitlog::LogSink::ptr file_lsp = bitlog::SinkFactory::create<bitlog::FileSink>("./logfile/test.log");
    bitlog::LogSink::ptr roll_lsp = bitlog::SinkFactory::create<bitlog::RollBySizeSink>("./logfile/roll-",1024*1024);

    std::vector<bitlog::LogSink::ptr> sinks = {stdout_lsp, file_lsp, roll_lsp};
    bitlog::Logger::ptr logger(new bitlog::SyncLogger(logger_name, limit, fmt, sinks));

    logger->debug(__FILE__, __LINE__, "%s", "厕所日志");
    logger->info(__FILE__, __LINE__, "%s", "厕所日志");
    logger->warn(__FILE__, __LINE__, "%s", "厕所日志");
    logger->error(__FILE__, __LINE__, "%s", "厕所日志");
    logger->fatal(__FILE__, __LINE__, "%s", "厕所日志");


    size_t cursize = 0;
    size_t count = 0;
    while(cursize<1024*1024*10)
    {
        logger->fatal(__FILE__, __LINE__, "测试日志-%d", count++);
        cursize += 20;
    }
    // bitlog::LogMsg msg(bitlog::LogLevel::value::INFO,53,"main.c","root","格式化测试...");
    // //bitlog::Formatter fmt("abc%%abc%g%g%g[%d{%H:%M:%S}] %m%n%g");
    // bitlog::Formatter fmt;
    // std::string str  = fmt.format(msg);
    // std::cout<<str<<std::endl;
    // bitlog::LogSink::ptr stdout_lsp = bitlog::SinkFactory::create<bitlog::StdoutSink>();
    // bitlog::LogSink::ptr file_lsp = bitlog::SinkFactory::create<bitlog::FileSink>("./logfile/test.log");
    // bitlog::LogSink::ptr roll_lsp = bitlog::SinkFactory::create<bitlog::RollBySizeSink>("./logfile/roll-",1024*1024);
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
    // std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::DEBUG)<<std::endl;
    // std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::INFO)<<std::endl;
    // std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::WARN)<<std::endl;
    // std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::ERROR)<<std::endl;
    // std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::FATAL)<<std::endl;
    // std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::OFF)<<std::endl;
    // std::cout<<bitlog::util::date::now()<<std::endl;
    // std::string path = "./abc/bcd/a.txt";
    // bitlog::util::file::create_directory(bitlog::util::file::path(path));
    return 0;
}