#ifndef CONNECTION_HPP
#define CONNECTION_HPP

class Connection;

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

#include "../common/Packet.hpp"
#include "WizardDisplay.hpp"
#include "PacketManager.hpp"

class Connection {
    /* Structure and fd for TCP connection */
    struct sockaddr_in _server_addr;
    struct hostent *_host;
    int _socketfd;

    pthread_t _thread;
    static void* receive(void*);
    public:
        Connection(std::string);
        ~Connection();
        void send_packet(void*, size_t);
        inline int get_socket() {return _socketfd;}
};

#endif /* CONNECTION_HPP */
