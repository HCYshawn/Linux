#include<iostream>
#include<cstdio>

int main()
{
    std::cout<<"hello cout"<<std::endl;
    printf("hello printf\n");

    std::cerr<<"hello cerr"<<std::endl;
    fprintf(stderr,"hello stderr\n");
    return 0;
}