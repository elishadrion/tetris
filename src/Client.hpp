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
#include "Game.hpp"
#include "dependencies/picosha2.h"

#define MAXPACKETSIZE 1024

class Client {

    public:
        Client();
        void start();
        void login();
        void signup();
        void receive();
        void manage();
        void pre_menu();
        void post_menu();
        void exiting();
        std::string get_hash(const std::string&);

    private:
    	int sockfd;
    	bool logged_in;
    	bool is_exiting;
	    struct hostent *hostinfo;
	    struct sockaddr_in server_address;
};

#endif
