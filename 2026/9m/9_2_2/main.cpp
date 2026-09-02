
#include <iostream>
#include <pthread.h>
#include <ctime>
#include <unistd.h>
#include "RingQueue.hpp"

void *consumer(void *args)
{
    RingQueue<int> *rq = static_cast<RingQueue<int> *>(args);
    while (true)
    {
        sleep(3);
        int t = 0;
        rq->Pop(&t);

        std::cout << "消费者拿到了一个数据: " << t << std::endl;
    }
}

void *productor(void *args)
{
    RingQueue<int> *rq = static_cast<RingQueue<int> *>(args);
    int data = 1;
    while (true)
    {

        std::cout << "生产了一个任务: " << data << std::endl;

        rq->Equeue(data);

        data++;
    }
}

int main()
{
    // 申请阻塞队列
    RingQueue<int> *rq = new RingQueue<int>();

    pthread_t c[1], p[1];
    pthread_create(c, nullptr, consumer, rq);
    pthread_create(p, nullptr, productor, rq);

    pthread_join(c[0], nullptr);
    pthread_join(p[0], nullptr);

    return 0;
}