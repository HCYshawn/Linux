#include"util.hpp"
#include"level.hpp"
#include"message.hpp"
#include"format.hpp"

int main()
{

    bitlog::LogMsg msg(bitlog::LogLevel::value::INFO,53,"main.c","root","格式化测试...");
    bitlog::Formatter fmt("abc%%abc%g%g%g[%d{%H:%M:%S}] %m%n%g");
    //bitlog::Formatter fmt;
    std::string str  = fmt.format(msg);
    std::cout<<str<<std::endl;
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