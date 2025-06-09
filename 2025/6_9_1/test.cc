#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <utmp.h>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <cmath>

// 统一的进度条显示函数（宽度50字符）
std::string get_progress_bar(float percent) {
    const int width = 50;
    int filled = std::min(static_cast<int>(percent * width), width);
    
    std::string bar = "[";
    for (int i = 0; i < width; ++i) {
        if (i < filled) bar += '=';
        else if (i == filled) bar += '>';
        else bar += ' ';
    }
    bar += "] " + std::to_string(static_cast<int>(percent * 100)) + "%";
    return bar;
}

// 修复CPU使用率计算
float get_cpu_usage() {
    static unsigned long long last_total = 0, last_idle = 0;
    
    std::ifstream stat_file("/proc/stat");
    std::string line;
    std::getline(stat_file, line);
    stat_file.close();
    
    std::istringstream iss(line);
    std::string cpu_label;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    iss >> cpu_label >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    
    unsigned long long total = user + nice + system + irq + softirq + steal + iowait;
    unsigned long long idle_time = idle + iowait;
    
    float usage = 0.0f;
    if (last_total != 0 && total > last_total) {
        unsigned long long total_diff = total - last_total;
        unsigned long long idle_diff = idle_time - last_idle;
        usage = (total_diff > 0) ? std::max(0.0f, (1.0f - static_cast<float>(idle_diff) / total_diff)) : 0.0f;
    }
    
    last_total = total;
    last_idle = idle_time;
    
    return usage;
}

// 获取内存使用率
float get_memory_usage() {
    std::ifstream meminfo("/proc/meminfo");
    std::string line;
    long total_mem = 0, free_mem = 0, buffers = 0, cached = 0;
    
    while (getline(meminfo, line)) {
        if (line.find("MemTotal:") == 0) sscanf(line.c_str(), "MemTotal: %ld kB", &total_mem);
        else if (line.find("MemFree:") == 0) sscanf(line.c_str(), "MemFree: %ld kB", &free_mem);
        else if (line.find("Buffers:") == 0) sscanf(line.c_str(), "Buffers: %ld kB", &buffers);
        else if (line.find("Cached:") == 0) sscanf(line.c_str(), "Cached: %ld kB", &cached);
    }
    meminfo.close();
    
    long used_mem = total_mem - free_mem - buffers - cached;
    return std::min(1.0f, static_cast<float>(used_mem) / total_mem);
}

// 获取磁盘I/O使用率
float get_disk_io_usage() {
    static unsigned long long last_read = 0, last_write = 0;
    
    std::ifstream io_file("/proc/diskstats");
    std::string line;
    unsigned long long reads = 0, writes = 0;
    
    while (getline(io_file, line)) {
        if (line.find("sda ") == 0 || line.find("sdb ") == 0) {
            std::istringstream iss(line);
            unsigned long long dummy, read_sectors, write_sectors;
            for (int i = 0; i < 6; ++i) iss >> dummy;
            iss >> read_sectors;
            for (int i = 0; i < 3; ++i) iss >> dummy;
            iss >> write_sectors;
            reads += read_sectors;
            writes += write_sectors;
        }
    }
    io_file.close();
    
    float usage = 0.0f;
    if (last_read != 0 && last_write != 0) {
        unsigned long long total_io = (reads - last_read) + (writes - last_write);
        usage = std::min(1.0f, static_cast<float>(total_io) / 5000.0f); // 比例系数
    }
    
    last_read = reads;
    last_write = writes;
    
    return usage;
}

// 获取在线用户列表
std::vector<std::string> get_logged_in_users() {
    std::vector<std::string> users;
    setutent();
    struct utmp *ut;
    
    while ((ut = getutent()) != nullptr) {
        if (ut->ut_type == USER_PROCESS) {
            users.push_back(ut->ut_user);
        }
    }
    endutent();
    
    return users;
}

// 主监控循环
void monitor_loop() {
    const int line_count = 7; // 更新为7行显示
    const std::string clear_lines = "\033[" + std::to_string(line_count) + "A\r";
    
    while (true) {
        // 获取当前时间
        std::time_t now = std::time(nullptr);
        std::tm *now_tm = std::localtime(&now);
        char time_buf[20];
        std::strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", now_tm);
        
        // 获取系统数据
        float cpu_usage = get_cpu_usage();
        float mem_usage = get_memory_usage();
        float disk_io_usage = get_disk_io_usage();
        auto users = get_logged_in_users();
        
        // 获取主机名和运行时间
        char hostname[256];
        gethostname(hostname, sizeof(hostname));
        struct sysinfo info;
        sysinfo(&info);
        int uptime_days = info.uptime / (60 * 60 * 24);
        int uptime_hours = (info.uptime % (60 * 60 * 24)) / (60 * 60);
        
        // 原地刷新显示
        std::cout << clear_lines;
        
        // 按新顺序输出信息
        std::cout << "当前时间："<<time_buf<<"\n";
        
        // 在线用户显示
        std::cout << "在线用户: ";
        for (size_t i = 0; i < users.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << users[i];
        }
        std::cout << "\n";
        
        // 主机信息
        std::cout << "主机: " << hostname << " | 运行: " << uptime_days << "天" << uptime_hours << "小时\n";
        
        // 资源使用率（统一进度条格式）
        std::cout << "CPU使用:  " << get_progress_bar(cpu_usage) << "\n";
        std::cout << "内存使用: " << get_progress_bar(mem_usage) << "\n";
        std::cout << "磁盘I/O:  " << get_progress_bar(disk_io_usage) << "\n";
        
        std::cout << std::flush;
        
        std::cout <<" 系统监控运行中...按Ctrl+C退出\n";
        // 等待1秒
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    // 初始清屏
    std::cout << "\033[2J\033[H";
    
    try {
        monitor_loop();
    } catch (...) {
        std::cout << "\n监控已终止\n";
    }
    
    return 0;
}
