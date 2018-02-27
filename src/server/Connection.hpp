#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <thread>
#include <system_error>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "../common/Constants.hpp"
#include "../common/Packet.hpp"
#include "../common/WizardLogger.hpp"
#include "PacketManager.hpp"
#include "Player.hpp"
#include "PlayerManager.hpp"

#define BACKLOG 5       /* Pending connections the queue will hold */

class Connection {
    /* Structure and fd for TCP connection */
    struct sockaddr_in _server_addr;
    struct sockaddr_in _client_addr; 
    int _server_socket;
    int _reuse = 1;
    bool _running;
    pthread_t _mythread;
    unsigned int _sin_size;

    static void* manage_player(void*);

    /* Temp send methode only used for login */
    static void send_response(int, int);
    static void send_success(Player*, int);

    public:
        Connection();
        ~Connection();
        void start();
        void stop() {_running = false;}
};

#endif /* CONNECTION_HPP */
