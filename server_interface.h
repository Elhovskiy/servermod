#ifndef SERVER_INTERFACE_H
#define SERVER_INTERFACE_H

#include <unordered_map>
#include <string>
#include <stdexcept>

class ServerInterface {
public:
    // Конструктор, принимающий аргументы командной строки
    ServerInterface(int argc, char* argv[]);

    // Метод для запуска сервера
    int startServer(const std::unordered_map<std::string, std::string>& clients, const std::string& logFile, int port);

    // Геттеры
    std::string getClientDBFile() const;
    std::string getLogFile() const;
    int getPort() const;

private:
    // Вспомогательная функция для старта сервера
    int startServerImplementation(const std::unordered_map<std::string, std::string>& clients, const std::string& logFile, int port);

    // Переменные, которые хранят информацию о конфигурации
    std::string clientDBFile;
    std::string logFile;
    int port;

    // Метод для обработки аргументов командной строки
    void parseArguments(int argc, char* argv[]);
};

#endif // SERVER_INTERFACE_H



