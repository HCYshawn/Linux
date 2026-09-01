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
        // sleep(1);
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
        sleep(1);
        std::cout << "生产了一个任务: " << std::endl;
        bq->Equeue(Download);
    }
}

int main()
{
    // 申请阻塞队列
    BlockQueue<task_t> *bq = new BlockQueue<task_t>();

    pthread_t c, p;
    pthread_create(&c, nullptr, consumer, bq);
    pthread_create(&p, nullptr, productor, bq);

    pthread_join(c, nullptr);
    pthread_join(p, nullptr);

    return 0;
}