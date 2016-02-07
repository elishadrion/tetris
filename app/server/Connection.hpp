#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#define PORT "5555"
#define BACKLOG 5 		/* Pending connections the queue will hold */
#define MAXDATASIZE 200

/**
 * Helper class to handle all incoming connections from clients and
 * threading them to treat them separately.
 */
class Connection {
    socklen_t sin_size;
    pthread_t thread_id;
    struct sockaddr_in6 guest;

    struct addrinfo* get_machine_info(void) const;
    int prepare_socket(struct addrinfo*) const;
public:
    void mainloop();
};

#endif /* CONNECTION_HPP */
