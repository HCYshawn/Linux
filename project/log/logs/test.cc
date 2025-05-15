#include"util.hpp"

int main()
{
    std::cout<<bitlog::util::date::now()<<std::endl;
    std::string path = "./abc/bcd/a.txt";
    bitlog::util::file::create_directory(bitlog::util::file::path(path));
    return 0;
}