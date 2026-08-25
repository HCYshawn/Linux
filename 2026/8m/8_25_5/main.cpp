#include <pthread.h>
#include <iostream>
#include <string>
#include <unistd.h>

// 加上'__'后，该count即线程的局部存储
__thread int count = 1;

std::string Addr(int &c)
{
    char addr[64];
    snprintf(addr, sizeof(addr), "%p", &c);
    return addr;
}

void *routine1(void *args)
{
    (void)args;
    while (true)
    {
        std::cout << "thread - 1, cout = " << count << "[我来修改count], " << "&count: " << Addr(count) << std::endl;
        count++;
        sleep(1);
    }
}

void *routine2(void *args)
{
    (void)args;
    while (true)
    {
        std::cout << "thread - 1, cout = " << count << "[我来修改count]" << "&count: " << Addr(count) << std::endl;

        sleep(1);
    }
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, nullptr, routine1, nullptr);
    pthread_create(&tid2, nullptr, routine2, nullptr);

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);
    return 0;
}