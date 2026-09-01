#include "BlockQueue.hpp"
#include "Task.hpp"
#include <iostream>
#include <pthread.h>
#include <ctime>
#include <unistd.h>

void *consumer(void *args)
{
    BlockQueue<task_t> *bq = static_cast<BlockQueue<task_t> *>(args);
    while (true)
    {
        // 1.消费任务
        sleep(3);
        task_t t = bq->Pop();
        // 2. 处理任务，此任务进入线程上下文，不再属于队列
        t();
    }
}

void *productor(void *args)
{

    BlockQueue<task_t> *bq = static_cast<BlockQueue<task_t> *>(args);
    while (true)
    {
        // sleep(1);
        std::cout << "生产了一个任务: " << std::endl;
        bq->Equeue(Download);
    }
}

int main()
{
    // 申请阻塞队列
    BlockQueue<task_t> *bq = new BlockQueue<task_t>();

    pthread_t c[1], p[1];
    pthread_create(c, nullptr, consumer, bq);
    // pthread_create(c + 1, nullptr, consumer, bq);
    pthread_create(p, nullptr, productor, bq);
    // pthread_create(p + 1, nullptr, productor, bq);
    // pthread_create(p + 2, nullptr, productor, bq);

    pthread_join(c[0], nullptr);
    // pthread_join(c[1], nullptr);
    pthread_join(p[0], nullptr);
    // pthread_join(p[1], nullptr);
    // pthread_join(p[2], nullptr);

    return 0;
}