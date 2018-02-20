#include <cstdlib>
#include <iostream>
#include <system_error>

#include "Connection.hpp"
#include "CacheManager.hpp"
#include "Player.hpp"
#include "common/WizardLogger.hpp"

#include <stdlib.h>     /* srand, rand */

Connection *conn;
Display *display;
Player *player;


int main() {
    /* Check if we launch as CLI or GUI and get adress */
    std::string address = "127.0.0.1";

    try {
        WizardLogger::initLogger(activeGUI, "WizardLogger");
    } catch (std::exception ex) {
        std::cerr << "Impossible d'initialiser le logger : " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    WizardLogger::info("Starting client");

    try {
        conn = new Connection((char*) address.c_str());
    } catch (...) {
        std::cerr << "Communication impossible avec le serveur (voir log)" << std::endl;
        return EXIT_FAILURE;
    }


    display->displayLoginPrompt();
    
    delete display;
    delete conn;


    return EXIT_SUCCESS;
}
