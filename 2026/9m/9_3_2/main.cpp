#include "Log.hpp"
#include <memory>

using namespace LogModule;

int main()
{
    Enable_Console_Log_Strategy();
    LOG(LogLevel::DEBUG) << "hello world";
    LOG(LogLevel::DEBUG) << "hello world";
    LOG(LogLevel::DEBUG) << "hello world";

    return 0;
}