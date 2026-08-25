#ifndef _THREAD_H_
#define _THREAD_H_

#include <iostream>
#include <string>
#include <pthread.h>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <functional>

namespace ThreadModlue
{
    static uint32_t number = 1;

    template <typename T>
    class Thread
    {
        using func_t = std::function<void(T)>;

    private:
        void EnableDetach()
        {
            std::cout << "线程被分离" << std::endl;
            _isdetach = true;
        }

        void EnableRunning()
        {
            _isrunning = true;
        }

        static void *Routine(void *args)
        {
            Thread<T> *self = static_cast<Thread<T> *>(args);
            self->EnableRunning();
            if (self->_isdetach)
                self->Detach();
            // self->EnableRunning();

            self->_func(self->_data);

            return nullptr;
        }

    public:
        Thread(func_t func, T data) : _tid(0), _isdetach(false), _isrunning(false), _res(nullptr), _func(func), _data(data)
        {
            _name = "thread-" + std::to_string(number++);
        }

        void Detach()
        {
            if (_isdetach)
                return;
            if (_isrunning)
                pthread_detach(_tid);
            EnableDetach();
        }

        bool Start()
        {
            if (_isrunning)
                return false;
            int n = pthread_create(&_tid, nullptr, Routine, this);
            if (n != 0)
            {
                std::cerr << "create thread error: " << strerror(n) << std::endl;
                return false;
            }
            else
            {
                std::cout << "start success" << std::endl;
                return true;
            }
        }

        bool Stop()
        {
            if (_isrunning)
            {
                int n = pthread_cancel(_tid);
                if (n != 0)
                {
                    std::cerr << "cancel thread error: " << strerror(n) << std::endl;
                    return false;
                }
                else
                {
                    _isrunning = false;
                    std::cout << _name << " stop " << std::endl;
                    return true;
                }
            }

            return false;
        }

        void Join()
        {
            if (_isdetach)
            {
                std::cout << "线程已分离, 不得join" << std::endl;
                return;
            }

            int n = pthread_join(_tid, &_res);
            if (n != 0)
            {
                std::cerr << "join thread error: " << strerror(n) << std::endl;
            }
            else
            {
                std::cout << "join success" << std::endl;
            }
        }

        ~Thread()
        {
        }

    private:
        pthread_t _tid;
        std::string _name;
        bool _isdetach;
        bool _isrunning;
        void *_res;
        func_t _func;
        T _data;
    };
}

#endif