#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx1;
std::mutex mtx2;

void func1()
{
    mtx1.lock();
    mtx2.lock();
    std::cout << "func1() get mtx1,mtx2" << std::endl;
    mtx1.unlock();
    mtx2.unlock();
}

void func2()
{
    mtx1.lock();
    mtx2.lock();
    std::cout << "func2() get mtx1,mtx2" << std::endl;
    mtx1.unlock();
    mtx2.unlock();
}

int main()
{
    std::thread t1(func1);
    std::thread t2(func2);

    t1.join();
    t2.join();
    return 0;
}