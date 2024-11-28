#include "VectorProcessor.h"
#include "Utils.h"
#include "DatabaseConnector.h"
#include <UnitTest++/UnitTest++.h>
#include <vector>
#include <fstream>
#include <unordered_map>

// ======================
// Тесты для VectorProcessor
// ======================
TEST(VectorProcessor_ComputeSumBasic) {
    VectorProcessor processor;
    std::vector<int16_t> vec = {30000, 20000, 3, 4};
    CHECK_EQUAL(10, processor.computeSum(vec));
}

TEST(VectorProcessor_ComputeSumOverflow) {
    VectorProcessor processor;
    std::vector<int16_t> vec = {INT16_MAX, 1};
    CHECK_EQUAL(INT16_MAX, processor.computeSum(vec));
}

TEST(VectorProcessor_ComputeSumUnderflow) {
    VectorProcessor processor;
    std::vector<int16_t> vec = {INT16_MIN, -1};
    CHECK_EQUAL(INT16_MIN, processor.computeSum(vec));
}

// ======================
// Тесты для Utils
// ======================
TEST(Utils_GenerateSaltLength) {
    std::string salt = Utils::generateSalt();
    CHECK_EQUAL(16, salt.size()); // Проверяем, что соль длиной 16 символов
}

TEST(Utils_HashWithSHA256) {
    std::string input = "test";
    std::string hash = Utils::hashWithSHA256(input);

    // Проверяем, что длина SHA-256 хэша равна 64 символам
    CHECK_EQUAL(64, hash.size());
}

// ======================
// Тесты для DatabaseConnector
// ======================
void createTestDB(const std::string& filename) {
    std::ofstream dbFile(filename);
    dbFile << "user1:hash1\n";
    dbFile << "user2:hash2\n";
    dbFile.close();
}

TEST(DatabaseConnector_LoadDatabase) {
    std::string testDB = "test_clients.txt";
    createTestDB(testDB);

    auto clients = DatabaseConnector::loadClientDatabase(testDB);
    CHECK_EQUAL(2, clients.size());
    CHECK_EQUAL("hash1", clients["user1"]);
    CHECK_EQUAL("hash2", clients["user2"]);

    // Удаляем тестовый файл после завершения
    std::remove(testDB.c_str());
}

// ======================
// Основная функция для запуска тестов
// ======================
int main() {
    return UnitTest::RunAllTests();
}

