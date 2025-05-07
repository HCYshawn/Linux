#include<iostream>
using namespace std;

int main()
{
    int a = 10;
    int & ra1 = a;
    const int& ra3 = 10;
    const int& ra4 = a;

    cout<<&a<<endl;
    cout<<&ra1<<endl;
    cout<<&ra3<<endl;
    cout<<&ra4<<endl;
    return 0;
}