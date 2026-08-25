#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <cstdio>
#include <cstring>

int *p = nullptr;

void *threadrun(void *args)
{
    int a = 123;
    p = &a;
    while (true)
    {
        sleep(1);
    }
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, threadrun, nullptr);

    sleep(1);
    while (true)
    {
        std::cout << "*p : " << *p << std::endl;
        sleep(1);
    }

    pthread_join(tid, nullptr);
    return 0;
}
