#include"util.hpp"
#include"level.hpp"
#include"message.hpp"
#include"format.hpp"
#include"sink.hpp"

int main()
{

    bitlog::LogMsg msg(bitlog::LogLevel::value::INFO,53,"main.c","root","格式化测试...");
    //bitlog::Formatter fmt("abc%%abc%g%g%g[%d{%H:%M:%S}] %m%n%g");
    bitlog::Formatter fmt;
    std::string str  = fmt.format(msg);
    std::cout<<str<<std::endl;
    bitlog::LogSink::ptr stdout_lsp = bitlog::SinkFactory::create<bitlog::StdoutSink>();
    bitlog::LogSink::ptr file_lsp = bitlog::SinkFactory::create<bitlog::FileSink>("./logfile/test.log");
    bitlog::LogSink::ptr roll_lsp = bitlog::SinkFactory::create<bitlog::RollBySizeSink>("./logfile/roll-",1024*1024);
    stdout_lsp->log(str.c_str(),str.size());
    file_lsp->log(str.c_str(),str.size());
    size_t cursize = 0;
    size_t count = 0;
    while(cursize<1024*1024*10)
    {
        std::string tmp = str+std::to_string(count++);
        roll_lsp->log(str.c_str(),str.size());
        cursize += tmp.size();
    }
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