#include <cstdlib>
#include <iostream>
#include <exception>
#include <csignal>


#include "Connection.hpp"
#include "CardManager.hpp"

#include "common/WizardLogger.hpp"

#include "Effect.hpp"

PlayerManager *pm;
Connection *conn;

void interrupt_handler(int signum) {
    WizardLogger::info("Signal ");
    delete conn;
    exit(0);
}



int main() {
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = interrupt_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, nullptr);


    /* Init Logger with both file and console log */
    try {
        WizardLogger::initLogger(true, "WizardLoggerServer");
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    WizardLogger::info("Starting server");


    // Load Effect
    Effect::loadAllEffect();

    // Loads card
    CardManager::loadAllCards();


    pm = new PlayerManager();
    pm -> loadPlayers();
    /* We initialise the listening server socket
     * If it fail, server can't go farther
     */
    Connection *conn;
    try {
        conn = new Connection();
    } catch (...) {
        return EXIT_FAILURE;
    }

    WizardLogger::info("Ecoute des tentatives de connexion des clients...");
    conn->mainLoop();

    delete conn;
    return EXIT_SUCCESS;
}
