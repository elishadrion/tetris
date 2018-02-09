#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAXPACKETSIZE 1024

class Client {

    public:
        Client();
        void login();
        void* receive(void*);
        void* send(void*);

    private:
    	int sockfd;
	    struct hostent *hostinfo;
	    struct sockaddr_in server_address;
	    pthread_t thread_receive, thread_send;
}

#endif