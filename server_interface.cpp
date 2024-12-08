#include "server_interface.h"
#include "server.h"      // Для функционала запуска сервера
#include "logger.h"      // Логирование
#include "database.h"    // Для загрузки базы данных клиентов

#include <iostream>

ServerInterface::ServerInterface(int argc, char* argv[]) {
    parseArguments(argc, argv);
}

void ServerInterface::parseArguments(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <client_db_file> <log_file> [port]" << std::endl;
        throw std::invalid_argument("Недостаточно аргументов");
    }

    clientDBFile = argv[1];
    logFile = argv[2];
    port = (argc > 3) ? std::stoi(argv[3]) : 22852;
}

int ServerInterface::startServer(const std::unordered_map<std::string, std::string>& clients, const std::string& logFile, int port) {
    try {
        // Вместо рекурсии передаем управление в функцию для запуска сервера
        return startServerImplementation(clients, logFile, port);
    } catch (const std::exception &e) {
        logError(logFile, "CRITICAL", e.what());
        return EXIT_FAILURE;
    }
}

// Функция для настоящего запуска сервера
int ServerInterface::startServerImplementation(const std::unordered_map<std::string, std::string>& clients, const std::string& logFile, int port) {
    // Логика для старта сервера
    return startServer(clients, logFile, port);  // Вызов функции для запуска сервера (например, из модуля server)
}

// Геттеры
std::string ServerInterface::getClientDBFile() const {
    return clientDBFile;
}

std::string ServerInterface::getLogFile() const {
    return logFile;
}

int ServerInterface::getPort() const {
    return port;
}




