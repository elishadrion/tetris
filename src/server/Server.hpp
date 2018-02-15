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
#include <mutex>
#include <fstream>
#include <list>
#include <algorithm>
#include "User.hpp"
#include "Room.hpp"
#include "../dependencies/CSVparser/CSVparser.hpp"

#define MAXPACKETSIZE 1024

class Server {

    public:
        Server(int port);
        ~Server();
        void stop();
        void accept_clients();
        std::string signup(char*);
        std::string login(User*, char*);
        void receive(int);
        void send_message(std::string msg);

        void extract_credentials(std::string&, std::string&, std::string&);
        bool user_already_connected(const std::string&);
        bool user_already_existing(const std::string&);
        
        void delete_user(User*);

    private:
        int _server, _client;
        std::mutex _mutex;
        bool _is_running;
        std::list<User*> _users;
        std::list<Room*> _rooms;
        socklen_t _sin_size;
        struct sockaddr_in _server_address;
        struct sockaddr_in _client_address;
};

#endif
