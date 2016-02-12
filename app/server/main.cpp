#include <cstdlib>
#include <iostream>
#include <exception>


#include "Connection.hpp"
#include "CardManager.hpp"
#include "common/Logger.hpp"


int main(int argc, char** argv) {
    /* Init the logger system (must be in a try-catch statment) */
    WizardLogger *log = new WizardLogger(true);
    log->debug("Je suis un debug");
    log->info("Je suis une info");
    log->warn("Je suis un warning");
    log->error("Je suis une erreur");
    log->fatal("Je suis une fatal");
    /* END OF DEMO */

    log->info("Starting server");

    // Load card
    //CardManager::loadCards();

    // Start listener
    Connection::mainloop();
    return 0;
}

void* handler(void* new_fd) {
    // sockfd to communicate with client.
    int sockfd = *static_cast<int*>(new_fd);

    // Game, login, etc... different calls


    // Example: stream server printing what the clients are saying

    size_t numbytes;
    char buf[MAXDATASIZE];
    while ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0))) {
        buf[numbytes] = '\0';

        printf("server - received '%s'\n", buf);
    }

    close(sockfd);
    return nullptr;
}
