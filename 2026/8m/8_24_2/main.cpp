#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>

class Task
{
public:
    Task(int a, int b) : _a(a), _b(b) {}
    int Execute()
    {
        return _a + _b;
    }
    ~Task() {}

private:
    int _a;
    int _b;
};

class Result
{
public:
    Result(int result) : _result(result)
    {
    }
    int GetResult() { return _result; }
    ~Result() {}

private:
    int _result;
};

void *routine(void *args)
{
    Task *t = static_cast<Task *>(args);
    sleep(100);
    Result *res = new Result(t->Execute());
    sleep(1);
    return res;
}

int main()
{
    pthread_t tid;
    Task *t = new Task(10, 20);
    pthread_create(&tid, nullptr, routine, t);

    sleep(3);
    pthread_cancel(tid);
    std::cout << "新线程被取消" << std::endl;

    void *ret = nullptr;
    pthread_join(tid, &ret);

    std::cout << "新线程结束, 运行结果: " << (long long)ret << std::endl;

    delete t;
    return 0;
}