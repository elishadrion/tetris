#include <cstdlib>
#include <iostream>
#include <exception>

#include "Connection.hpp"
#include "CardManager.hpp"

#include "common/WizardLogger.hpp"

#include "Effect.hpp"

PlayerManager *pm;

int main() {
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
