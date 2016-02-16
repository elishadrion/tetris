#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "Connection.hpp"
#include "common/WizardLogger.hpp"
#include "Console.hpp"

int main(int argc, char** argv) {
    /* Init Logger, actually we are only console mode
     * So we cannot use console log (for now)
     */
    try {
        WizardLogger::initLogger(false, "WizardLogger");
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    WizardLogger::info("Starting client");
    
    Console::init();
    
    //Connection::connect_to_host(argv[1]);
    
    Console::close();

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
