#include <cstdlib>
#include <iostream>
#include <stdexcept>


#include "Connection.hpp"
#include "common/WizardLogger.hpp"

/* Public WizardLogger pointer to use it everywhere */
WizardLogger *logger;

int main(int argc, char** argv) {
    /* Init Logger, actually we are only console mode
     * So we cannot use console log (for now)
     */
    try {
        logger = new WizardLogger(false);
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    Connection::connect_to_host(argv[1]);

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
