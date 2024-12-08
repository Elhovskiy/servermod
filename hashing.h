#ifndef HASHING_H
#define HASHING_H

#include <string>

std::string generateSalt();
std::string hashWithSHA256(const std::string &input);

#endif // HASHING_H
