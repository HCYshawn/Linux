#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <memory>

int main()
{
    std::string json_string = "{\"name\":\"张三\", \"age\":30, \"city\":\"北京\"}";

    Json::Value root;
    Json::Reader reader;

    bool ok = reader.parse(json_string, root);
    (void)ok;

    std::string name = root["name"].asString();
    int age = root["age"].asInt();
    std::string city = root["city"].asString();

    std::cout << name << std::endl;
    std::cout << age << std::endl;
    std::cout << city << std::endl;

    return 0;
}