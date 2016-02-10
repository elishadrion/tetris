#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <csignal>
#include <pthread.h>

#define PORT "5555"
#define BACKLOG 5       /* Pending connections the queue will hold */
#define MAXDATASIZE 200

namespace Connection {
    struct addrinfo* get_machine_info(void);
    int prepare_socket(struct addrinfo* machine_info);
    void mainloop();
}


#endif /* CONNECTION_HPP */
