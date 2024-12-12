/**
 * @file database.cpp
 * @brief Загрузка базы данных клиентов.
 * 
 * Этот файл содержит функцию для загрузки базы данных клиентов из файла.
 */
#include "database.h"
#include <fstream>
#include <stdexcept>

/**
 * @brief Загружает базу данных клиентов из файла.
 * 
 * Функция читает файл и извлекает идентификаторы и хэши клиентов.
 * 
 * @param dbFile Путь к файлу базы данных.
 * @return Словарь клиентов с их хэшами.
 * @throws std::runtime_error Если не удается открыть файл базы данных.
 */
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

