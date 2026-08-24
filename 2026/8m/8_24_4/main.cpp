#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <cstdio>
#include <cstring>

const int num = 10;

void *routine(void *args)
{
    std::string name = static_cast<const char *>(args);
    delete (char *)args;
    int cnt = 5;
    while (cnt--)
    {
        std::cout << "new线程名字: " << name << std::endl;
        sleep(1);
    }
    return nullptr;
}

int main()
{
    std::vector<pthread_t> tids;
    for (int i = 0; i < num; i++)
    {
        pthread_t tid;
        char *id = new char[64];
        snprintf(id, 64, "thread-%d", i);
        int n = pthread_create(&tid, nullptr, routine, id);
        if (n == 0)
            tids.push_back(tid);
        else
            continue;
        sleep(1);
    }

    for (int i = 0; i < num; i++)
    {
        int n = pthread_join(tids[i], nullptr);
        if (n == 0)
        {
            std::cout << "等待新线程成功" << std::endl;
        }
        sleep(1);
    }

    return 0;
}
