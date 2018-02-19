#include <cstdlib>
#include <iostream>
#include <exception>
#include <csignal>


#include "Connection.hpp"
#include "../common/WizardLogger.hpp"

Connection *conn;

int main() {

    std::cout << "Démarrage serveur" << std::endl;
    WizardLogger::initLogger(true, "WizardLoggerServer");
    WizardLogger::info("Démarrage serveur");

    try {
        conn = new Connection();
    } catch (...) {
        return EXIT_FAILURE;
    }
	WizardLogger::info("Ecoute des tentatives de connexions");
    conn->start();

    delete conn;
    return 0;
}
