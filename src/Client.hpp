#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <thread>
#include <netdb.h>
#include "dependencies/PicoSHA2/picosha2.h"

#define MAXPACKETSIZE 1024

class Client {

    public:
        Client();
        void start();
        void login();
        void signup();
        void receive(int);
        void send_message(int);
        std::string get_hash(const std::string&);

    private:
    	int sockfd;
	    struct hostent *hostinfo;
	    struct sockaddr_in server_address;
};

#endif
