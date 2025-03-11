#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <sys/stat.h>
#include <dirent.h>
#include <cerrno>
#include <cstring>

using namespace std;

int main() 
{
    // 获取当前时间
    time_t now = time(nullptr);
    if (now == -1) 
    {
        cerr << "Error getting current time." << endl;
        return 1;
    }

    struct tm tm_struct;
    localtime_r(&now, &tm_struct);
    int month = tm_struct.tm_mon + 1; // tm_mon是0-11，所以加1
    int day = tm_struct.tm_mday;

    // 生成目录名前缀，如3_11_
    ostringstream prefix_stream;
    prefix_stream << month << "_" << day << "_";
    string prefix = prefix_stream.str();

    // 遍历当前目录，查找最大序号
    DIR *dir = opendir(".");
    if (dir == nullptr) 
    {
        cerr << "Error opening current directory: " << strerror(errno) << endl;
        return 1;
    }

    int max_num = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) 
    {
        struct stat statbuf;
        if (lstat(entry->d_name, &statbuf) == -1) continue;

        // 检查是否为目录
        if (!S_ISDIR(statbuf.st_mode)) continue;

        string name = entry->d_name;
        if (name.compare(0, prefix.length(), prefix) == 0) 
        {
            string suffix = name.substr(prefix.length());
            try 
            {
                size_t pos;
                int num = stoi(suffix, &pos);
                if (pos == suffix.length() && num > max_num) 
                {
                    max_num = num;
                }
            }
            catch (const exception&) 
            {
                continue;
            }
        }
    }
    closedir(dir);

    // 创建新目录
    ostringstream dirname_stream;
    dirname_stream << prefix << (max_num + 1);
    string dirname = dirname_stream.str();

    if (mkdir(dirname.c_str(), 0755) == -1) {
        cerr << "Error creating directory: " << strerror(errno) << endl;
        return 1;
    }

    cout << "Created directory: " << dirname << endl;
    return 0;
}