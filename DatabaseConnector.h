#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <unordered_map>
#include <string>

class DatabaseConnector {
public:
    static std::unordered_map<std::string, std::string> loadClientDatabase(const std::string& dbFile);
};

#endif
