/**
 * @file server.cpp
 * @brief Сервер, обрабатывающий запросы клиентов.
 * 
 * Этот файл содержит функцию для запуска сервера и обработки запросов клиентов.
 */
#include "server.h"
#include "logger.h"
#include "client_handler.h"
#include "database.h"
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

/**
 * @brief Запускает сервер.
 * 
 * Создает сокет, привязывает его к адресу и порту, и начинает слушать входящие соединения.
 * Принимает подключения и передает их для обработки функции handleClient.
 * 
 * @param clientDBFile Путь к файлу базы данных клиентов.
 * @param logFile Путь к файлу журнала.
 * @param port Порт для прослушивания (по умолчанию 22852).
 * @return Код возврата.
 * @throws std::runtime_error При ошибках с сокетами или подключениями.
 */
int startServer(const std::string &clientDBFile, const std::string &logFile, int port) {
    auto clients = loadClientDatabase(clientDBFile);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) throw std::runtime_error("Ошибка создания сокета.");

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        throw std::runtime_error("Ошибка привязки сокета.");

    if (listen(serverSocket, 5) < 0)
        throw std::runtime_error("Ошибка запуска прослушивания.");

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            logError(logFile, "WARNING", "Ошибка подключения клиента.");
            continue;
        }
        handleClient(clientSocket, clients, logFile);
    }

    close(serverSocket);
    return 0;
}

