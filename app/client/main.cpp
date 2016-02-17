#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "Connection.hpp"
#include "common/WizardLogger.hpp"
#include "Display.hpp"
#include "CLI.hpp"
//#include "GUI.hpp"

int main(int argc, char** argv) {
    /* Init Logger, actually we are only in console mode
     * So we cannot use console log (for now)
     */
    try {
        WizardLogger::initLogger(false, "WizardLogger");
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    WizardLogger::info("Starting client");
    
    /* We init in CLI mode */
    Display *display = new CLI();
    
    //Connection::connect_to_host(argv[1]);
    
    /* We close all interface */
    delete display;

    return 0;
}

// Il faut remplacer ca!!!
void handler(int sockfd) {
    std::string line;
    char buf[MAXDATASIZE];
    while (std::getline(std::cin, line)) {
	strcpy(buf, line.c_str());
	send(sockfd, buf, sizeof line, 0);
    }
}
