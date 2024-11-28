#include "ClientHandler.h"
#include "DatabaseConnector.h"
#include "Logger.h"
#include <iostream>
#include <unordered_map>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <stdexcept>
#include <csignal>

constexpr int DEFAULT_PORT = 33333;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <client_db_file> <log_file> [port]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string clientDBFile = argv[1];
    std::string logFile = argv[2];
    int port = (argc > 3) ? std::stoi(argv[3]) : DEFAULT_PORT;

    // Игнорирование сигнала SIGPIPE, чтобы сервер не завершался при закрытии соединения
    signal(SIGPIPE, SIG_IGN);

    try {
        // Загрузка базы данных клиентов
        auto clients = DatabaseConnector::loadClientDatabase(clientDBFile);

        // Создание сокета
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) throw std::runtime_error("Ошибка создания сокета.");

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
            throw std::runtime_error("Ошибка привязки сокета.");

        if (listen(serverSocket, 5) < 0) throw std::runtime_error("Ошибка запуска прослушивания.");

        std::cout << "Сервер запущен на порту " << port << std::endl;

        // Основной цикл для обработки клиентов
        while (true) {
            sockaddr_in clientAddr{};
            socklen_t clientLen = sizeof(clientAddr);

            // Принимаем подключение клиента
            int clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientLen);
            if (clientSocket < 0) {
                Logger::logError(logFile, "WARNING", "Ошибка подключения клиента.");
                continue; // Не завершаем сервер
            }

            // Логируем факт подключения клиента
            std::cout << "Клиент подключился." << std::endl;

            // Обработка клиента в отдельном потоке
            std::thread clientThread([clientSocket, &clients, &logFile]() {
                try {
                    std::cout << "Обработка клиента началась." << std::endl;
                    ClientHandler::handleClient(clientSocket, clients, logFile);
                    std::cout << "Обработка клиента завершена." << std::endl;
                } catch (const std::exception &e) {
                    Logger::logError(logFile, "ERROR", e.what());
                } catch (...) {
                    Logger::logError(logFile, "ERROR", "Неизвестная ошибка в клиентском потоке.");
                }
                close(clientSocket);  // Закрытие сокета клиента после завершения работы
                std::cout << "Сокет клиента закрыт." << std::endl;
            });

            // Отсоединяем поток для обработки следующего клиента
            clientThread.detach();
        }

        close(serverSocket); // Этот код не будет выполнен, так как сервер всегда ожидает подключения

    } catch (const std::exception &e) {
        Logger::logError(logFile, "CRITICAL", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
