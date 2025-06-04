#ifndef __M_LOOPER_H__
#define __M_LOOPER_H__

#include "buffer.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <memory>

namespace bitlog
{
    using Functor = std::function<void(Buffer &)>;
    class AsyncLooper
    {
    public:
        void stop()
        {
        }
        void push(const char *data, size_t len)
        {
        }

    private:
        // 线程入口函数
        void threadEntry()
        {
        }

    private:
        // 具体对缓冲区数据进行处理的回调函数，由异步工作器使用者传入
        Functor _callBack;
        //
    private:
        bool _stop;      // 工作器停止标志
        Buffer _pro_buf; // 生产缓冲区
        Buffer _con_buf; // 消费缓冲区
        std::mutex _mutex;
        std::condition_variable _cond_pro;
        std::condition_variable _cond_con;
        std::thread _thread; // 异步工作器对应的工作线程
    };
}

#endif