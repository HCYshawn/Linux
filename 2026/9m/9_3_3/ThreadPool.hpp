#pragma once

#include "Cond.hpp"
#include "Log.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace ThreadPoolModule {
using namespace ThreadModlue;
using namespace LogModule;
using namespace CondModule;
using namespace MutexModule;

static const int gnum = 5;

template <typename T> class ThreadPool {
public:
  ThreadPool(int num = gnum) : _num(num) {
    for (int i = 0; i < num; i++) {
      _threads.emplace_back([this]() { HandlerTask(); });
    }
  }

  void Start() {
    for (auto &thread : _threads) {
      thread.Start();
    }
  }

  void HandlerTask() {
    char name[128];
    pthread_getname_np(pthread_self(), name, sizeof(name));
    while (true) {
      // sleep(1);
      // LOG(LogLevel::DEBUG) << name << " is running ";

      T t;
      {
        LockGuard lockguard(_mutex);
        while (_taskq.empty()) {
          _cond.Wait(_mutex);
        }

        // 到此一定有任务
        t = _taskq.front();
        _taskq.pop();
      }
      // t();
    }
  }

  ~ThreadPool() {}

private:
  std::vector<Thread> _threads;
  int _num; // 线程池中线程的个数
  std::queue<T> _taskq;
  Cond _cond;
  Mutex _mutex;
};
} // namespace ThreadPoolModule
