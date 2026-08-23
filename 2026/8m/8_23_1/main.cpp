#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>

void *threadrun(void *args)
{
    std::string name = (const char *)args;
    while (true)
    {
        std::cout << "我是一个新线程: name: " << name << ", pid: " << getpid() << std::endl;
        sleep(1);
    }
    return nullptr;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, threadrun, (void *)"thread-1");

    while (true)
    {
        std::cout << "我是一个主线程..." << ", pid: " << getpid() << std::endl;
        sleep(1);
    }
    return 0;
}