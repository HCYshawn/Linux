#include"util.hpp"
#include"level.hpp"


int main()
{
    std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::DEBUG)<<std::endl;
    std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::INFO)<<std::endl;
    std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::WARN)<<std::endl;
    std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::ERROR)<<std::endl;
    std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::FATAL)<<std::endl;
    std::cout<<bitlog::LogLevel::toString(bitlog::LogLevel::value::OFF)<<std::endl;
    // std::cout<<bitlog::util::date::now()<<std::endl;
    // std::string path = "./abc/bcd/a.txt";
    // bitlog::util::file::create_directory(bitlog::util::file::path(path));
    return 0;
}