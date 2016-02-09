#include <cstdlib>
#include <iostream>


#include "Connection.hpp"

int main(int argc, char** argv) {
    Connection ConnectionService;
    ConnectionService.connect_to_host(argv[1]);

    return 0;
}

void handler(int sockfd) {
    std::string line;
    char buf[MAXDATASIZE];
    while (std::getline(std::cin, line)) {
	strcpy(buf, line.c_str());
	send(sockfd, buf, sizeof line, 0);
    }
}
