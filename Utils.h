#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    static std::string generateSalt();
    static std::string hashWithSHA256(const std::string& input);
};

#endif
