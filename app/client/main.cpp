#include <cstdlib>
#include <iostream>
#include <system_error>

#include "Connection.hpp"
#include "common/WizardLogger.hpp"
#include "Display.hpp"
#include "CLI.hpp"
//#include "GUI.hpp"

/* Main is not an object so we must use global namespace instead of main->conn */
Connection *conn;

Display *display;

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
    
    /* We initialise the connection between client and server
     * By the way, we initialise tchat socket
     * If agument is provide, use it as hostName, if not we try localhost
     * If it fail, client can't go farther
     */
    try {
        argc > 1 ? conn = new Connection(argv[1]) : conn = new Connection((char*)"localhost");
    } catch (...) {
        std::cerr << "Communication impossible avec le serveur (voir log)" << std::endl;
        return EXIT_FAILURE;
    }
    
    /* We init in CLI mode */
    display = new CLI();
    
    /* Display login prompt
     * Only call it after all backround service are ready
     * User become the only one to can modify program state
     */
    display->displayLoginPrompt();
    
    /* We close all interface */
    delete display;
    delete conn;
    return EXIT_SUCCESS;
}
