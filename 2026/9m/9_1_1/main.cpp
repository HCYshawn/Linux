#include "BlockQueue.hpp"
#include "Task.hpp"
#include <iostream>
#include <pthread.h>
#include <ctime>
#include <unistd.h>

void *consumer(void *args)
{
    BlockQueue<Task> *bq = static_cast<BlockQueue<Task> *>(args);
    while (true)
    {
        sleep(1);
        Task t = bq->Pop();
        t.Execute();

        std::cout << "消费了一个任务: " << t.X() << " + " << t.Y() << " = " << t.Result() << std::endl;
    }
}

void *productor(void *args)
{
    int x = 1;
    int y = 1;
    BlockQueue<Task> *bq = static_cast<BlockQueue<Task> *>(args);
    while (true)
    {
        sleep(1);
        std::cout << "生产了一个任务: " << x << " + " << y << " = ?" << std::endl;
        Task t(x, y);
        bq->Equeue(t);

        x++;
        y++;
    }
}

int main()
{
    // 申请阻塞队列
    BlockQueue<Task> *bq = new BlockQueue<Task>();

    pthread_t c, p;
    pthread_create(&c, nullptr, consumer, bq);
    pthread_create(&p, nullptr, productor, bq);

    pthread_join(c, nullptr);
    pthread_join(p, nullptr);

    return 0;
}