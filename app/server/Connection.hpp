#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <vector>
#include <system_error>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <pthread.h>

#include "common/Constants.hpp"
#include "common/Packet.hpp"
#include "PacketManager.hpp"
#include "Player.hpp"
#include "PlayerManager.hpp"

#define BACKLOG 5       /* Pending connections the queue will hold */

extern PlayerManager *pm;

class Connection {
    /* Structure and fd for TCP connection */
    struct sockaddr_in server_addr; //TODO don't support IPv6
    struct sockaddr_in client_addr; //TODO don't support IPv6
    int _serverSocket;
    unsigned int _sinSize;
    
    /* Correct non opening socket after crash */
    int _reuse = 1;
    
    /* Active TCP keep alive protocole */
    int _keepon = 1;
    /* The time (in seconds) the connection needs to remain 
     * idle before TCP starts sending keepalive probes
     * (TCP_KEEPIDLE socket option)
     */
    int _keepidle = 60;
    /* The maximum number of keepalive probes TCP should 
     * send before dropping the connection (TCP_KEEPCNT socket option)
     */
    int _keepcnt = 5;
    /* The time (in seconds) between individual keepalive probes
     * (TCP_KEEPINTVL socket option)
     */
    int _keepintvl = 5;
    
    /* Thread for non blocking all program for each player */
    pthread_t _newThread;
    static void* newPlayerThread(void* data);
    
    /* Temp send methode only used for login */
    static void sendResponse(int, int);
    static void sendSucess(Player*, int);
public:
    Connection();
    ~Connection();
    void mainLoop();
};

#endif /* CONNECTION_HPP */
