#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "common/Packet.hpp"

#define PORT 5555
#define MAXDATASIZE 200

/**
namespace Connection {
    int socked;
    void* get_in_addr(struct sockaddr*);
    struct addrinfo* get_server_info(char*);
    int prepare_socket(struct addrinfo*);
    void connect_to_host(char*);
    void close_connection();
    void sendPacket(Packet*, int);
}
**/

class Connection {
    struct sockaddr_in server_addr;
    struct hostent *host;
    int clientSocket;
    bool connected;
public:
    Connection(char*);
    ~Connection();
    bool isConnected();
    void sendPacket(Packet*, long unsigned int);
};

#endif /* CONNECTION_HPP */
