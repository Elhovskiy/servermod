#include "database.h"
#include <fstream>
#include <stdexcept>

std::unordered_map<std::string, std::string> loadClientDatabase(const std::string &dbFile) {
    std::unordered_map<std::string, std::string> clients;
    std::ifstream inFile(dbFile);
    if (!inFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл базы данных клиентов.");
    }
    std::string line;
    while (std::getline(inFile, line)) {
        auto delimiterPos = line.find(':');
        if (delimiterPos != std::string::npos) {
            std::string id = line.substr(0, delimiterPos);
            std::string hash = line.substr(delimiterPos + 1);
            clients[id] = hash;
        }
    }
    return clients;
}
