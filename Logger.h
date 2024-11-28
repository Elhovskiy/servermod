#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    static void logError(const std::string& logFile, const std::string& level, const std::string& message);
};

#endif
