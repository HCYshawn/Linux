#include "Log.hpp"
#include <memory>

using namespace LogModule;

int main()
{
    // std::unique_ptr<LogStrategy> strategy = std::make_unique<ConsoleLogStrategy>();
    std::unique_ptr<LogStrategy> strategy = std::make_unique<FileLogStrategy>();

    strategy->SyncLog("hello log!");
    return 0;
}