/**
 * @file database.h
 * @brief Заголовочный файл для работы с базой данных клиентов.
 * 
 * Этот файл содержит декларацию функции для загрузки базы данных клиентов из файла.
 */
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <unordered_map>

/**
 * @brief Загружает базу данных клиентов из файла.
 * 
 * Функция читает файл базы данных, где каждый клиент представлен строкой в формате "id:hash",
 * и возвращает словарь с клиентами.
 * 
 * @param dbFile Путь к файлу базы данных.
 * @return Словарь клиентов, где ключ — это идентификатор клиента, а значение — хэш.
 * @throws std::runtime_error Если файл базы данных не может быть открыт.
 */
std::unordered_map<std::string, std::string> loadClientDatabase(const std::string &dbFile);

#endif // DATABASE_H

