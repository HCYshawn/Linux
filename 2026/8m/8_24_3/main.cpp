#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <cstdio>
#include <cstring>

void *routine(void *args)
{
    int cnt = 5;
    while (cnt--)
    {
        std::cout << "new线程..." << std::endl;
        sleep(1);
    }
    return nullptr;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, routine, (void *)"thread-1");

    pthread_detach(tid);
    std::cout << "新线程被分离" << std::endl;

    int cnt = 5;
    while (cnt--)
    {
        std::cout << "main线程..." << std::endl;
        sleep(1);
    }

    int n = pthread_join(tid, nullptr);
    if (n != 0)
    {
        std::cout << "pthread_join error: " << strerror(n) << std::endl;
    }
    else
    {
        std::cout << "pthread_join success: " << strerror(n) << std::endl;
    }

    return 0;
}