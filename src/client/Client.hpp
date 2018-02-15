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
#include "../game/Game.hpp"
#include "../dependencies/picosha2.h"

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
    	int _sockfd;
    	bool _logged_in;
    	bool _is_exiting;
	    struct hostent *_hostinfo;
	    struct sockaddr_in _server_address;
};

#endif
