#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

#define PORT "5555"
#define MAXDATASIZE 200

class Connection {
    char hostname[INET6_ADDRSTRLEN];
    //struct addrinfo *server_info, *p;


    struct addrinfo* get_server_info(char*) const;
    int prepare_socket(struct addrinfo*) const;
public:
    void connect_to_host(char*);
};


#endif /* CONNECTION_H */
