#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <unistd.h>

#include "../common/Packet.hpp"
#include "PacketManager.hpp"
#include "WizardDisplay.hpp"

extern WizardDisplay *wizardDisplay;

class Connection {
    /* Structure and fd for TCP connection */
    struct sockaddr_in _server_addr;
    struct hostent *_host;
    int _socketfd;

    pthread_t _thread;
    static void* receive(void*);
public:
    Connection(char*);
    ~Connection();
    void send_packet(Packet::packet*, size_t);
};

#endif /* CONNECTION_HPP */
