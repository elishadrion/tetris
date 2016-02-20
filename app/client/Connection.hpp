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
#include "CommService.hpp"

#define PORT 5555

class Connection {
    struct sockaddr_in server_addr;
    struct hostent *host;
    int _clientSocket;
    pthread_t _recvThread;
    
    static void* recvLoop(void* data);
public:
    Connection(char*);
    ~Connection();
    void sendPacket(Packet*, long unsigned int);
};

#endif /* CONNECTION_HPP */
