#include <UnitTest++/UnitTest++.h>
#include "logger.h"
#include "hashing.h"
#include "vector_processor.h"
#include "database.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <limits>
#include <stdexcept>

// ====== Тесты для логирования ======
SUITE(LoggerTests) {
    TEST(LogError_FileCreated) {
        std::string logFile = "test.log";
        logError(logFile, "ERROR", "Test message");

        std::ifstream inFile(logFile);
        CHECK(inFile.is_open());

        inFile.close();
        std::remove(logFile.c_str());
    }

    TEST(LogError_ContentWritten) {
        std::string logFile = "test.log";
        logError(logFile, "INFO", "This is a test log entry.");

        std::ifstream inFile(logFile);
        std::string logContent;
        std::getline(inFile, logContent);

        CHECK(logContent.find("INFO") != std::string::npos);
        CHECK(logContent.find("This is a test log entry.") != std::string::npos);

        inFile.close();
        std::remove(logFile.c_str());
    }
}

// ====== Тесты для хэширования ======
SUITE(HashingTests) {
    TEST(GenerateSalt_Unique) {
        std::string salt1 = generateSalt();
        std::string salt2 = generateSalt();
        CHECK(salt1 != salt2);
    }

    TEST(GenerateSalt_Length) {
        std::string salt = generateSalt();
        CHECK_EQUAL(16, salt.size());
    }

    TEST(HashWithSHA256_Valid) {
        std::string input = "test";
        std::string hash = hashWithSHA256(input);
        CHECK(!hash.empty());
        CHECK_EQUAL(64, hash.size());
    }

    TEST(HashWithSHA256_DifferentInputs) {
        std::string hash1 = hashWithSHA256("input1");
        std::string hash2 = hashWithSHA256("input2");
        CHECK(hash1 != hash2);
    }
}

// ====== Тесты для обработки векторов ======
SUITE(VectorProcessorTests) {
    TEST(ComputeSum_Normal) {
        VectorProcessor processor;
        std::vector<int16_t> vec = {1, 2, 3, 4};
        CHECK_EQUAL(10, processor.computeSum(vec));
    }

    TEST(ComputeSum_OverflowPositive) {
        VectorProcessor processor;
        std::vector<int16_t> vec = {std::numeric_limits<int16_t>::max(), 1};
        CHECK_EQUAL(std::numeric_limits<int16_t>::max(), processor.computeSum(vec));
    }

    TEST(ComputeSum_OverflowNegative) {
        VectorProcessor processor;
        std::vector<int16_t> vec = {std::numeric_limits<int16_t>::min(), -1};
        CHECK_EQUAL(std::numeric_limits<int16_t>::min(), processor.computeSum(vec));
    }

    TEST(ComputeSum_EmptyVector) {
        VectorProcessor processor;
        std::vector<int16_t> vec;
        CHECK_EQUAL(0, processor.computeSum(vec));
    }

    TEST(ComputeSum_SingleElement) {
        VectorProcessor processor;
        std::vector<int16_t> vec = {42};
        CHECK_EQUAL(42, processor.computeSum(vec));
    }
}

// ====== Тесты для базы данных клиентов ======
SUITE(DatabaseTests) {
    TEST(LoadClientDatabase_ValidFile) {
        std::string dbFile = "test.db";
        std::ofstream outFile(dbFile);
        outFile << "client1:hash1\nclient2:hash2\n";
        outFile.close();

        auto clients = loadClientDatabase(dbFile);
        CHECK_EQUAL(2, clients.size());
        CHECK_EQUAL("hash1", clients["client1"]);
        CHECK_EQUAL("hash2", clients["client2"]);

        std::remove(dbFile.c_str());
    }

    TEST(LoadClientDatabase_EmptyFile) {
        std::string dbFile = "empty.db";
        std::ofstream outFile(dbFile);
        outFile.close();

        auto clients = loadClientDatabase(dbFile);
        CHECK_EQUAL(0, clients.size());

        std::remove(dbFile.c_str());
    }

    TEST(LoadClientDatabase_FileNotFound) {
        CHECK_THROW(loadClientDatabase("nonexistent.db"), std::runtime_error);
    }

    TEST(LoadClientDatabase_InvalidFormat) {
        std::string dbFile = "invalid.db";
        std::ofstream outFile(dbFile);
        outFile << "client1:hash1\nclient2hash2\n";
        outFile.close();

        auto clients = loadClientDatabase(dbFile);
        CHECK_EQUAL(1, clients.size());
        CHECK(clients.find("client2hash2") == clients.end());

        std::remove(dbFile.c_str());
    }
}

// ====== Основная функция ======
int main() {
    return UnitTest::RunAllTests();
}
