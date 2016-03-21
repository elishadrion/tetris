#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <unistd.h>

#include "common/Packet.hpp"
#include "PacketManager.hpp"
#include "common/WizardLogger.hpp"
#include "WizardDisplay.hpp"

extern WizardDisplay *wizardDisplay;

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
public:
    Connection(char*);
    ~Connection();
    void sendPacket(Packet::packet*, size_t);
    void recvPacket();
};

#endif /* CONNECTION_HPP */
