#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include "Mutex.hpp"

int ticket = 1000;

using namespace MutexModule;

class ThreadData
{
public:
    ThreadData(const std::string &n, Mutex &lock)
        : name(n),
          lockp(&lock)
    {
    }
    ~ThreadData() {}
    std::string name;
    Mutex *lockp;
};

void *route(void *arg)
{
    ThreadData *td = static_cast<ThreadData *>(arg);
    while (true)
    {
        LockGuard guard(*td->lockp); // 加锁完成
        // pthread_mutex_lock(td->lockp);
        if (ticket > 0)
        {
            usleep(1000);
            printf("%s sells ticket:%d\n", td->name.c_str(), ticket);
            ticket--;
            // pthread_mutex_unlock(td->lockp);
            //td->lockp->Unlock();
        }
        else
        {
            //td->lockp->Unlock();
            // pthread_mutex_unlock(td->lockp);
            break;
        }
    }
    return nullptr;
}

int main()
{
    Mutex lock;
    // pthread_mutex_init(&lock, nullptr);
    pthread_t t1, t2, t3, t4;

    ThreadData *td1 = new ThreadData("thread-1", lock);
    pthread_create(&t1, nullptr, route, td1);
    ThreadData *td2 = new ThreadData("thread-1", lock);
    pthread_create(&t2, nullptr, route, td2);
    ThreadData *td3 = new ThreadData("thread-1", lock);
    pthread_create(&t3, nullptr, route, td3);
    ThreadData *td4 = new ThreadData("thread-1", lock);
    pthread_create(&t4, nullptr, route, td4);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    pthread_join(t4, nullptr);

    // pthread_mutex_destroy(&lock);

    return 0;
}