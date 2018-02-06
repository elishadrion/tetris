#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAXPACKETSIZE 1024

class Server {

    public:
        Server(int port);

    private:
        int server, client, n;
        struct sockaddr_in serverAddress, clientAddress;
        pthread_t thread;
        char msg[MAXPACKETSIZE];

        void receive();
        void send(string msg);
}

#endif