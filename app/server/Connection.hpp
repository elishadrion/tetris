#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <system_error>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "common/Packet.hpp"
#include "PacketManager.hpp"

#define PORT 5555
#define BACKLOG 5       /* Pending connections the queue will hold */

class Connection {
    struct sockaddr_in server_addr; //TODO don't support IPv6
    struct sockaddr_in client_addr; //TODO don't support IPv6
    int _serverSocket;
    unsigned int _sinSize;
public:
    Connection();
    ~Connection();
    void mainLoop();
};

#endif /* CONNECTION_HPP */
