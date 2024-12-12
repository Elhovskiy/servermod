/**
 * @file client_handler.cpp
 * @brief Обработчик клиентов для сервера.
 *
 * Этот файл содержит функцию обработки клиента, включая аутентификацию и обработку векторов.
 */
#include "client_handler.h"
#include "logger.h"
#include "hashing.h"
#include "vector_processor.h"
#include <vector>
#include <cstring>
#include <unistd.h>
#include <stdexcept>
#include <sys/socket.h>

/**
 * @brief Обрабатывает клиентский запрос.
 * 
 * Выполняет аутентификацию клиента, отправку соли, проверку хэша, а затем вычисление суммы элементов вектора.
 * 
 * @param clientSocket Сокет клиента для связи.
 * @param clients Словарь клиентов с хэшами.
 * @param logFile Путь к файлу журнала для записи ошибок.
 */
void handleClient(int clientSocket, const std::unordered_map<std::string, std::string> &clients, const std::string &logFile) {
    try {
        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) throw std::runtime_error("Ошибка при получении идентификатора.");

        std::string clientID(buffer, bytesReceived);
        auto it = clients.find(clientID);
        if (it == clients.end()) {
            send(clientSocket, "ERR", 3, 0);
            throw std::runtime_error("Клиент не найден: " + clientID);
        }

        std::string salt = generateSalt();
        send(clientSocket, salt.c_str(), salt.size(), 0);

        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) throw std::runtime_error("Ошибка при получении хэша.");

        std::string receivedHash(buffer, bytesReceived);
        std::string expectedHash = hashWithSHA256(salt + it->second);

        if (receivedHash != expectedHash) {
            send(clientSocket, "ERR", 3, 0);
            throw std::runtime_error("Ошибка аутентификации клиента: " + clientID);
        }

        send(clientSocket, "OK", 2, 0);

        uint32_t numVectors = 0;
        recv(clientSocket, &numVectors, sizeof(numVectors), 0);

        VectorProcessor processor;

        for (uint32_t i = 0; i < numVectors; ++i) {
            uint32_t vectorSize = 0;
            recv(clientSocket, &vectorSize, sizeof(vectorSize), 0);

            std::vector<int16_t> vec(vectorSize);
            recv(clientSocket, vec.data(), vectorSize * sizeof(int16_t), 0);

            int16_t result = processor.computeSum(vec);
            send(clientSocket, &result, sizeof(result), 0);
        }

    } catch (const std::exception &e) {
        logError(logFile, "ERROR", e.what());
    }
    close(clientSocket);
}

