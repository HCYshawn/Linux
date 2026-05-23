#include "logger.h"
#include "console_logger.h"

void log_message(const std::string &msg) { ConsoleLogger::log(msg); }
