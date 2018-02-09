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
#include <thread>

#include "User.hpp"

#define MAXPACKETSIZE 1024

class Server {

    public:
        Server(int port);
        void stop();
        void accept_clients();
        bool signup(char*);
        bool login(User*, char*);
        void receive(int);
        void send_message(std::string msg);

        void extract_credentials(std::string&, std::string&, std::string&);
        bool user_already_connected(const std::string&);
        bool user_already_existing(const std::string&);

    private:
        int server, client, n;
        bool is_running;
        //
        unsigned num_users;
        User* users[10];
        //
        socklen_t sin_size;
        struct sockaddr_in server_address;
        struct sockaddr_in client_address;
        pthread_t thread;
        char msg[MAXPACKETSIZE];
};

#endif
