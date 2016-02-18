#include <cstdlib>
#include <iostream>
#include <exception>

#include "Connection.hpp"
#include "CardManager.hpp"
#include "common/WizardLogger.hpp"

int main() {
    /* Init Logger with both file and console log */
    try {
        WizardLogger::initLogger(true, "WizardLoggerServer");
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    WizardLogger::info("Starting server");
    Connection *conn = new Connection();
    if (!conn->isReady()) {
        WizardLogger::fatal("Impossible d'écouter les clients");
        return EXIT_FAILURE;
    }
    
    conn->mainLoop();

    // Loads card
    //CardManager::loadCards();

    // Starts listener
    //Connection::mainloop();
    
    delete conn;
    return 0;
}
/**
void* handler(int &new_fd, int &listening_socket) {
    size_t numbytes;
    char buf[MAXDATASIZE];

    // Example: stream server printing what the clients are saying
    if ((numbytes = recv(new_fd, buf, sizeof buf, 0)) <= 0) {
	// got error or connection closed by client
	if (numbytes == 0) {
	    WizardLogger::warn("Connection closed by client, socket: %i");
	} else {
	    perror("server - error receiving - recv()");
	}
	close(new_fd);
	Connection::proper_fd_clr(new_fd, &Connection::master, &Connection::fdmax);
    } else {
	// everything is fine. let's check what the client sent
	// analysepacket();
    }

    return nullptr;
}**/
