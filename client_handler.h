/**
 * @file client_handler.h
 * @brief Заголовочный файл для обработки запросов клиентов.
 * 
 * Этот файл содержит объявление функции для обработки запросов клиентов,
 * включая аутентификацию и обработку векторов.
 */
#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <unordered_map>
#include <string>

/**
 * @brief Обрабатывает клиентский запрос.
 * 
 * Функция для обработки клиентского запроса. Она выполняет аутентификацию клиента,
 * отправляет соль для хэширования и вычисляет сумму элементов вектора.
 * 
 * @param clientSocket Сокет клиента для связи с сервером.
 * @param clients Словарь клиентов с хэшами.
 * @param logFile Путь к файлу журнала для записи ошибок.
 */
void handleClient(int clientSocket, const std::unordered_map<std::string, std::string> &clients, const std::string &logFile);

#endif // CLIENT_HANDLER_H
