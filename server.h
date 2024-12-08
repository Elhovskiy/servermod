#ifndef SERVER_H
#define SERVER_H

#include <string>

int startServer(const std::string &clientDBFile, const std::string &logFile, int port);

#endif // SERVER_H
