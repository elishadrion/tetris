#include <cstdlib>
#include <iostream>


#include "Connection.hpp"
#include "CardManager.hpp"


int main(int argc, char** argv) {

    std::cout << "-=- Starting server -=-" << std::endl;

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
