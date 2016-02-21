#include <cstdlib>
#include <iostream>
#include <exception>

#include "Connection.hpp"
#include "CardManager.hpp"

#include "common/WizardLogger.hpp"

#include "Effect.hpp"


int main() {
    /* Init Logger with both file and console log */
    try {
        WizardLogger::initLogger(true, "WizardLoggerServer");
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    WizardLogger::info("Starting server");

    // Loads card
    //CardManager::loadCards();

    // Load Effect
    Effect::loadAllEffect();


    /* We initialise the listening server socket
     * If it fail, server can't go farther
     */
    Connection *conn;
    try {
        conn = new Connection();
    } catch (std::system_error &error) {
        WizardLogger::fatal("Impossible d'écouter les clients", error);
        return EXIT_FAILURE;
    }

    WizardLogger::info("Ecoute des tentatives de connexion des clients...");
    conn->mainLoop();

    delete conn;
    return EXIT_SUCCESS;
}
