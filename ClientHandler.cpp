#include "ClientHandler.h"
#include "Logger.h"
#include "VectorProcessor.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <netinet/in.h>
#include <unistd.h>

void ClientHandler::handleClient(int clientSocket, const std::unordered_map<std::string, std::string>& clients, const std::string& logFile) {
    try {
        std::cout << "Начало обработки клиента." << std::endl;

        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cerr << "Ошибка: не удалось получить идентификатор клиента." << std::endl;
            return;
        }

        std::string clientID(buffer, bytesReceived);
        std::cout << "Получен идентификатор клиента: " << clientID << std::endl;

        auto it = clients.find(clientID);
        if (it == clients.end()) {
            send(clientSocket, "ERR", 3, 0);
            std::cerr << "Ошибка: клиент не найден." << std::endl;
            return;
        }

        std::string salt = Utils::generateSalt();
        send(clientSocket, salt.c_str(), salt.size(), 0);
        std::cout << "Сгенерированная соль: " << salt << std::endl;

        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cerr << "Ошибка: не удалось получить хэш." << std::endl;
            return;
        }

        std::string receivedHash(buffer, bytesReceived);
        std::string expectedHash = Utils::hashWithSHA256(salt + it->second);

        if (receivedHash != expectedHash) {
            send(clientSocket, "ERR", 3, 0);
            std::cerr << "Ошибка аутентификации клиента: " << clientID << std::endl;
            return;
        }
        send(clientSocket, "OK", 2, 0);
        std::cout << "Аутентификация клиента успешна: " << clientID << std::endl;

        uint32_t numVectors;
        recv(clientSocket, &numVectors, sizeof(numVectors), 0);
        numVectors = ntohl(numVectors);

        VectorProcessor processor;

        for (uint32_t i = 0; i < numVectors; ++i) {
            uint32_t vectorSize;
            recv(clientSocket, &vectorSize, sizeof(vectorSize), 0);
            vectorSize = ntohl(vectorSize);

            std::vector<int16_t> vec(vectorSize);
            recv(clientSocket, vec.data(), vectorSize * sizeof(int16_t), 0);

            int16_t result = processor.computeSum(vec);
            send(clientSocket, &result, sizeof(result), 0);
        }

    } catch (const std::exception& e) {
        std::cerr << "Исключение в обработке клиента: " << e.what() << std::endl;
        Logger::logError(logFile, "ERROR", e.what());
    } catch (...) {
        std::cerr << "Неизвестная ошибка в обработке клиента." << std::endl;
        Logger::logError(logFile, "ERROR", "Неизвестная ошибка в обработке клиента.");
    }

    std::cout << "Завершение обработки клиента. Закрытие сокета." << std::endl;
    close(clientSocket);
}



