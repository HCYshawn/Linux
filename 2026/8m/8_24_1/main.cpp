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
    sleep(1);
    Result *res = new Result(t->Execute());
    sleep(1);
    return res;
}

int main()
{
    pthread_t tid;
    Task *t = new Task(10, 20);
    pthread_create(&tid, nullptr, routine, t);

    Result *ret = nullptr;
    pthread_join(tid, (void **)&ret);
    int n = ret->GetResult();

    std::cout << "新线程结束, 运行结果: " << n << std::endl;

    delete t;
    delete ret;
    return 0;
}