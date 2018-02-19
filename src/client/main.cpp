#include <cstdlib>
#include <iostream>
#include <system_error>

#include <QApplication>


#include "Connection.hpp"
#include "CacheManager.hpp"
#include "Player.hpp"
#include "common/WizardLogger.hpp"
#include "WizardDisplay.hpp"
#include "CLI.hpp"
#include "GUI.hpp"

#include <stdlib.h>     /* srand, rand */

Connection *conn;
WizardDisplay *display;
CacheManager *cacheManager;
Player *player;


int main() {
    /* Check if we launch as CLI or GUI and get adress */
    std::string address = "localhost";

    try {
        conn = new Connection((char*) address.c_str());
    } catch (...) {
        std::cerr << "Communication impossible avec le serveur (voir log)" << std::endl;
        return EXIT_FAILURE;
    }

    cacheManager = new CacheManager();
    display = new CLI();

    display->displayLoginPrompt();
    
    delete display;
    delete conn;
    delete cacheManager;


    return EXIT_SUCCESS;
}
