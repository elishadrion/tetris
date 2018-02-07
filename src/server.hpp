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
#include "User.hpp"

#define MAXPACKETSIZE 1024

class Server {

    public:
        Server(int port);

    private:
        int server, client, n;
        bool is_running;
        //
        unsigned num_users;
        User users[10];
        //
        socklen_t sin_size;
        struct sockaddr_in server_address, client_address;
        pthread_t thread;
        char msg[MAXPACKETSIZE];

        void stop();
        void accept();
        bool signup(User *);
        bool login();
        void* receive(void* arg);
        void send(string msg);
}

#endif