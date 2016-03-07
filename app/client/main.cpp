#include <cstdlib>
#include <iostream>
#include <system_error>

#include <QApplication>


#include "Connection.hpp"
#include "CacheManager.hpp"
#include "common/WizardLogger.hpp"
#include "WizardDisplay.hpp"
#include "CLI.hpp"
#include "GUI.hpp"

/* Main is not an object so we must use global namespace instead of main->conn */
Connection *conn;
WizardDisplay *wizardDisplay;
CacheManager *cacheManager;

/**
 * View if argument is a GUI information or an IP adresse
 *
 * @param arg argument whitch must be test
 * @return True if it's an IP
 */
bool isIP(std::string arg) {
    for(unsigned int i=0; i < arg.size(); i++) {
        arg[i] = std::toupper(arg[i]);
    }

    return arg != "GUI" && arg != "CLI";
}


int main(int argc, char** argv) {
    /* We initialise the static logger system
     * If it fail, client must to stop because log is important !
     */
    try {
        WizardLogger::initLogger(false, "WizardLogger");
    } catch (std::exception ex) {
        std::cerr << "Impossible d'initialiser le logger : " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    WizardLogger::info("Starting client");
    
    std::string adress = "localhost";
    bool activeGUI = true;
    if(argc > 1) {
        std::string arg1 = argv[1];
        if(isIP(arg1)) {
            adress = arg1;
        } else {
            activeGUI = (arg1 == "GUI");
        }

        if(argc > 2) {
            std::string arg2 = argv[2];
            if(isIP(arg2)) {
                if(adress == "localhost") {
                    adress = arg2;
                } else {
                    std::string warnMsg = "Vous aviez déjà définit";
                    warnMsg += " l'adresse dans l'argument 1";
                    WizardLogger::warning(warnMsg);
                }
            } else {
                activeGUI = (arg2 == "GUI");
            }
        }
    }


    /* We initialise the connection between client and server
     * By the way, we initialise tchat socket
     * If agument is provide, use it as hostName, if not we try localhost
     * If it fail, client can't go farther
     */
    try {
        conn = new Connection((char*) adress.c_str());
    } catch (...) {
        std::cerr << "Communication impossible avec le serveur (voir log)" << std::endl;
        return EXIT_FAILURE;
    }

    /* We init the cacheManager */
    cacheManager = new CacheManager();

    QApplication app(argc, argv);
    if(activeGUI) {
        // TO DO
        wizardDisplay = new GUI();
    } else {
        /* We init in CLI mode
         * If it fail, client must stop
         */
        try {
            wizardDisplay = new CLI();
        } catch (...) {
            std::cerr << "Impossible de créer l'interface (voir log)" << std::endl;
            return EXIT_FAILURE;
        }
    }


    /* Display login prompt
     * Only call it after all backround service are ready
     * User become the only one to can modify program state
     */
    wizardDisplay->displayLoginPrompt();
    
    /* We close all interface */
    if(activeGUI) {
        app.exec();
    }
    delete wizardDisplay;
    delete conn;
    delete cacheManager;


    return EXIT_SUCCESS;
}
