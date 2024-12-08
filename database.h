#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> loadClientDatabase(const std::string &dbFile);

#endif // DATABASE_H
