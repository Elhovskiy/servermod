#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <unordered_map>
#include <string>

void handleClient(int clientSocket, const std::unordered_map<std::string, std::string> &clients, const std::string &logFile);

#endif // CLIENT_HANDLER_H
