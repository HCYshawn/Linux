#include<iostream>
#include<unistd.h>

int main()
{
    std::cout<<"hello cpp, My PID: "<<getpid()<<std::endl;
    return 0;
}