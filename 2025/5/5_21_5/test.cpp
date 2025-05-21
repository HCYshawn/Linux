#include <iostream>
#include <thread>
using namespace std;

void thread_1()
{
    while (1)
    {
    }
}

void thread_2(int x)
{
    while (1)
    {
    }
}

int main()
{
    thread first(thread_1);
    thread second(thread_2, 100);

    cout << "主线程\n";

    first.join();
    second.join();
    while (1)
    {
        cout << "主线程\n";
    }
    return 0;
}