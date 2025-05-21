#include <iostream>
#include <thread>
using namespace std;

void thread_1()
{
    while (1)
    {
        cout << "子线程111" << endl;
    }
}

void thread_2(int x)
{
    while (1)
    {
        cout << "子线程222" << endl;
    }
}

int main()
{
    thread first(thread_1);
    thread second(thread_2, 100);

    cout << "主线程\n";

    first.detach();
    second.detach();
    for (int i = 0; i < 10; i++)
    {
        cout << "主线程\n";
    }
    return 0;
}