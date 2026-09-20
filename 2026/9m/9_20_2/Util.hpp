#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Util
{
public:
    static bool ReadFileContent(const std::string &filename, std::string *out)
    {
        std::ifstream in(filename);
        if (!in.is_open())
            return false;

        std::string line;
        while (std::getline(in, line))
        {
            *out += line;
        }
        in.close();
        return true;
    }
};