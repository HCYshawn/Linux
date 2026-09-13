#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <string>

int main() {
  Json::Value root;
  root["name"] = "张三";
  root["sex"] = "男";
  root["age"] = "18";

  std::string s = root.toStyledString();
  std::cout << s << std::endl;

  return 0;
}
