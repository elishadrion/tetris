#include <cstdlib>
#include <iostream>
#include <exception>
#include <csignal>


#include "Connection.hpp"

Connection *conn;

void interrupt_handler(int signum) {
    std::cout << "Interrupt Signal" << std::endl;
    delete conn;
    exit(signum);
}

int main() {
    signal(SIGINT, interrupt_handler);

    std::cout << "Démarrage serveur" << std::endl;

    try {
        conn = new Connection();
    } catch (...) {
        return EXIT_FAILURE;
    }

    conn->start();

    delete conn;
    return 0;
}
