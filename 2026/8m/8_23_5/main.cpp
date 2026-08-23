#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <pthread.h>

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
    int cnt = 5;
    while (cnt)
    {
        std::cout << "我是一个新线程: name: " << name
                  << "我的id: " << FormatId(tid) << std::endl;
        sleep(1);
        cnt--;
    }
    return (void *)123;
}

int main()
{
    pthread_t tid;
    int n = pthread_create(&tid, nullptr, routine, (void *)"thread-1");
    (void)n;

    showtid(tid);

    int cnt = 5;
    while (cnt)
    {
        std::cout << "我是一个main线程, 我名字是main thread" << " 我的id: " << FormatId(pthread_self()) << std::endl;
        sleep(1);
        cnt--;
    }

    void *ret = nullptr;
    pthread_join(tid, &ret);
    std::cout << "ret is: " << (long long int)ret << std::endl;
    return 0;
}