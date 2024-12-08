#include "logger.h"
#include <fstream>
#include <ctime>
#include <iomanip>

void logError(const std::string &logFile, const std::string &level, const std::string &message) {
    std::ofstream outFile(logFile, std::ios::app);
    if (outFile.is_open()) {
        std::time_t now = std::time(nullptr);
        char timeBuffer[64];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        outFile << "[" << timeBuffer << "] [" << level << "] " << message << std::endl;
    }
}

