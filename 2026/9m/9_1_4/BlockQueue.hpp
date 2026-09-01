#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <pthread.h>

const int defaultcap = 5;

template <typename T>
class BlockQueue
{
private:
    bool IsFull() { return _q.size() >= _cap; }
    bool IsEmpty() { return _q.empty(); }

public:
    BlockQueue(int cap = defaultcap)
        : _cap(cap), _csleep_num(0), _psleep_num(0)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_full_cond, nullptr);
        pthread_cond_init(&_empty_cond, nullptr);
    }

    void Equeue(const T &in)
    {
        pthread_mutex_lock(&_mutex);
        // 生产者调用
        while (IsFull())
        {
            // wait调用成功后，挂起当前线程之前，需先自动释放锁
            // 当线程被唤醒时，默认就在临界区内唤醒，要从wait成功返回
            // 需要当前线程，重新申请_mutex锁
            // 若唤醒后申请锁失败，会在锁上阻塞等待
            _psleep_num++;
            std::cout << "生产者，进入休眠状态: _psleep_num: " << _psleep_num << std::endl;
            // wait可能会因为条件不满足，导致伪唤醒
            pthread_cond_wait(&_full_cond, &_mutex);
            _psleep_num--;
        }
        _q.push(in);

        // 唤醒消费者
        if (_csleep_num > 0)
        {
            pthread_cond_signal(&_empty_cond);
            std::cout << "唤醒消费者..." << std::endl;
        }

        pthread_mutex_unlock(&_mutex);
    }

    T Pop()
    {
        // 消费者调用
        pthread_mutex_lock(&_mutex);
        while (IsEmpty())
        {
            _csleep_num++;
            pthread_cond_wait(&_empty_cond, &_mutex);
            _csleep_num--;
        }
        T data = _q.front();
        _q.pop();

        // 唤醒生产者
        if (_psleep_num > 0)
        {
            pthread_cond_signal(&_full_cond);
            std::cout << "唤醒生产者..." << std::endl;
        }

        pthread_mutex_unlock(&_mutex);
        return data;
    }

    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_full_cond);
        pthread_cond_destroy(&_empty_cond);
    }

private:
    std::queue<T> _q; // 临界资源
    int _cap;         // 容量大小

    pthread_mutex_t _mutex;
    pthread_cond_t _full_cond;
    pthread_cond_t _empty_cond;

    int _csleep_num; // 消费者休眠个数
    int _psleep_num; // 生产者休眠个数
};