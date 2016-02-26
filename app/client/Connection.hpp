#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <pthread.h>

#include "common/Packet.hpp"
#include "PacketManager.hpp"
#include "common/WizardLogger.hpp"
#include "Display.hpp"

#define PORT 5555

extern Display *display;

class Connection {
    /* Structure and fd for TCP connection */
    struct sockaddr_in server_addr;
    struct hostent *host;
    int _clientSocket;
    
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
    
    /* Thread for non blocking all program when using recv */
    pthread_t _recvThread;
    static void* recvLoop(void* data);
public:
    Connection(char*);
    ~Connection();
    void sendPacket(Packet*, size_t);
};

#endif /* CONNECTION_HPP */
