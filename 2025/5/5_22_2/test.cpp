#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx_1;
std::mutex mtx_2;

int test_num = 1;

void print_block_1(int n, char c)
{
    mtx_1.lock();
    for (int i = 0; i < n; ++i)
    {
        test_num = 1;
        std::cout << test_num << std::endl;
    }
    mtx_1.unlock();
}

void print_block_2(int n, char c)
{
    mtx_2.lock();
    for (int i = 0; i < n; ++i)
    {
        test_num = 2;
        std::cout << test_num << std::endl;
    }
    mtx_2.unlock();
}

int main()
{
    std::thread th1(print_block_1, 50, '*');
    std::thread th2(print_block_2, 50, '$');

    th1.join();
    th2.join();
    return 0;
}