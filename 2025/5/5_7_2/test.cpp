#include"test.h"

void func1(bit::string s)
{

}

void func2(const bit::string& s)
{

}

int main()
{
    bit::string s1("hello world");
    func1(s1);
    func2(s1);
    return 0;
}