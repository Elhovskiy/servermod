#include "server.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <client_db_file> <log_file> [port]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string clientDBFile = argv[1];
    std::string logFile = argv[2];
    int port = (argc > 3) ? std::stoi(argv[3]) : 22852;

    return startServer(clientDBFile, logFile, port);
}




