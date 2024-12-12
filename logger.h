/**
 * @file logger.h
 * @brief Заголовочный файл для логирования.
 * 
 * Этот файл содержит объявление функции для записи ошибок в файл журнала.
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

/**
 * @brief Записывает ошибку в файл журнала.
 * 
 * Функция записывает ошибку в файл журнала с отметкой времени и уровнем ошибки.
 * 
 * @param logFile Путь к файлу журнала.
 * @param level Уровень ошибки (например, "ERROR", "WARNING").
 * @param message Сообщение ошибки.
 */
void logError(const std::string &logFile, const std::string &level, const std::string &message);

#endif // LOGGER_H

