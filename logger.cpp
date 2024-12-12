#include "logger.h"
#include <fstream>
#include <ctime>
#include <iomanip>

/**
 * @brief Записывает ошибку в файл журнала.
 * 
 * Функция записывает сообщение об ошибке в файл журнала с отметкой времени.
 * Ошибки могут быть разных уровней (например, "ERROR" или "WARNING").
 * 
 * @param logFile Путь к файлу журнала.
 * @param level Уровень ошибки (например, "ERROR", "WARNING").
 * @param message Сообщение ошибки.
 */
void logError(const std::string &logFile, const std::string &level, const std::string &message) {
    // Открытие файла журнала для добавления новой записи
    std::ofstream outFile(logFile, std::ios::app);
    
    // Если файл открыт успешно, записываем сообщение
    if (outFile.is_open()) {
        // Получаем текущее время
        std::time_t now = std::time(nullptr);
        char timeBuffer[64];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        
        // Записываем сообщение в журнал
        outFile << "[" << timeBuffer << "] [" << level << "] " << message << std::endl;
    }
}


