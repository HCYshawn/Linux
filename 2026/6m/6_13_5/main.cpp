#include<iostream>
#include"person.pb.h"

int main()
{
    // 1 创建Person对象
    example::Person person;
    person.set_name("Bit");
    person.set_id(10086);
    person.set_email("cmake@example.com");

    // 2 序列化 person对象
    std::string serialized_data;
    person.SerializeToString(&serialized_data);
    std::cout<<"Serialized size: "<<serialized_data.size()<<std::endl;

    // 3 反序列化 perosn对象
    example::Person parsed_person;
    parsed_person.ParseFromString(serialized_data);
    std::cout<<parsed_person.DebugString();


    return 0;
}


