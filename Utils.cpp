#include "Utils.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

std::string Utils::generateSalt() {
    uint64_t salt = static_cast<uint64_t>(rand()) << 32 | rand();
    std::stringstream ss;
    ss << std::uppercase << std::setfill('0') << std::setw(16) << std::hex << salt;
    return ss.str();
}

std::string Utils::hashWithSHA256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    std::stringstream ss;
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}
