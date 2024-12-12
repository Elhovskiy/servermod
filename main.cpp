#include "server.h"
#include <iostream>
#include <cstring>

/**
 * @brief Выводит справочную информацию о запуске сервера.
 * 
 * Функция выводит в консоль информацию о правильном использовании программы,
 * включая описание аргументов командной строки.
 */
void printHelp() {
    std::cout << "Usage: ./server <log_file> <db_file> [<port>]\n"     
              << "  Arguments:\n"
              << "    <log_file>  Path to the log file.\n"
              << "    <db_file>   Path to the database file.\n"
              << "    <port>      Optional port number (default 22852).\n";
}

/**
 * @brief Основная функция для запуска сервера.
 * 
 * Функция обрабатывает аргументы командной строки, выводит справочную информацию при необходимости,
 * загружает конфигурации и запускает сервер.
 * 
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк, содержащих аргументы командной строки.
 * @return Код возврата (0 — успешный запуск).
 */
int main(int argc, char *argv[]) {
    // Вывод справки, если передан параметр '-h' или нет аргументов
    if ((argc > 1 && (std::strcmp(argv[1], "-h") == 0)) || argc == 1 ) {
        printHelp();
        return 0;
    }

    // Проверка наличия минимального количества аргументов
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <client_db_file> <log_file> [port]\n"
                  << "Попробуй: ./server -h' for more information."<< std::endl;
        return EXIT_FAILURE;
    }

    // Чтение файлов конфигурации и порта
    std::string clientDBFile = argv[1];
    std::string logFile = argv[2];
    int port = (argc > 3) ? std::stoi(argv[3]) : 22852;

    // Запуск сервера
    return startServer(clientDBFile, logFile, port);
}





