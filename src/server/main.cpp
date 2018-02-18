#include <cstdlib>
#include <iostream>
#include <exception>
#include <csignal>


#include "Connection.hpp"

Connection *conn;

int main() {

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
