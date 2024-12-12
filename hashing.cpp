/**
 * @file hashing.cpp
 * @brief Функции для работы с хэшированием.
 * 
 * Этот файл содержит функции для генерации соли и хэширования данных.
 */
#include "hashing.h"
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <cstdlib>

/**
 * @brief Генерирует случайную соль.
 * 
 * Генерирует случайную 64-битную соль в формате шестнадцатеричной строки.
 * 
 * @return Строка, представляющая соль.
 */
std::string generateSalt() {
    uint64_t salt = static_cast<uint64_t>(rand()) << 32 | rand();
    std::stringstream ss;
    ss << std::uppercase << std::setfill('0') << std::setw(16) << std::hex << salt;
    return ss.str();
}

/**
 * @brief Хэширует строку с использованием алгоритма SHA-256.
 * 
 * @param input Строка для хэширования.
 * @return Хэш строки в шестнадцатеричном формате.
 */
std::string hashWithSHA256(const std::string &input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(input.c_str()), input.size(), hash);
    std::stringstream ss;
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

