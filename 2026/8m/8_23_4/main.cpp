#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <pthread.h>

int flag = 100;

void showtid(pthread_t &tid)
{
    printf("tid: 0x%lx\n", tid);
}

std::string FormatId(const pthread_t &tid)
{
    char id[64];
    snprintf(id, sizeof(id), "0x%lx", tid);
    return id;
}

void *routine(void *args)
{
    std::string name = static_cast<const char *>(args);
    pthread_t tid = pthread_self();
    while (true)
    {
        std::cout << "我是一个新线程: name: " << name
                  << "我的id: " << FormatId(tid) << std::endl;
        sleep(1);
        flag++;
    }
    return nullptr;
}

int main()
{
    pthread_t tid;
    int n = pthread_create(&tid, nullptr, routine, (void *)"thread-1");
    (void)n;

    showtid(tid);

    while (true)
    {
        std::cout << "我是一个main线程, 我名字是main thread" << " 我的id: " << FormatId(pthread_self()) << " flag: " << flag << std::endl;
        sleep(1);
    }

    pthread_join(tid, nullptr);
    return 0;
}