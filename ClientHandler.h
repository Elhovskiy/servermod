#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <unordered_map>
#include <string>

class ClientHandler {
public:
    static void handleClient(int clientSocket, const std::unordered_map<std::string, std::string>& clients, const std::string& logFile);
};

#endif
