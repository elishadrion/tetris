#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sys/socket.h>
#include "../dependencies/json.hpp"
#include "unistd.h"
#include "../common/Packet.hpp"
#include "PacketManager.hpp"
#include "../common/Constants.hpp"
#include "../common/WizardLogger.hpp"

#include "Room.hpp"

class Player {

    protected:
        std::string _username;
        int _sockfd;

        Room* _room;
        unsigned _victories;
        unsigned _defeats;

    public:
        #ifndef PLAYER_PACKET_THREAD_SAFE
        #define PLAYER_PACKET_THREAD_SAFE
        pthread_mutex_t packetStackMutex = PTHREAD_MUTEX_INITIALIZER;
        pthread_cond_t packetStackCond = PTHREAD_COND_INITIALIZER;
        std::vector<void*> packetStack;
        #endif
        //Player(nlohmann::json&, int sockfd = 0);
        //CONSTRUCTEUR ET DESTRUCTEUR
        Player(std::string username, int sockfd): _username(username), _sockfd(sockfd) {}
        virtual ~Player() {close(_sockfd); delete _room;}
        //GETTERS
        inline int get_sockfd() const {return _sockfd;}
        inline Player* get_player_ptr() {return this;}
        inline Room* get_room() {return _room;}
        inline std::string get_username() const {return _username;}
        inline unsigned get_victories() const {return _victories;}
        inline unsigned get_defeats() const {return _defeats;}
        //SETTERS
        inline void set_sockfd(int sock) {_sockfd = sock;}
        inline void increment_victories() {_victories++;}
        inline void increment_defeats() {_defeats++;}
        inline void set_room(Room* room) {_room = room;}
        //INTERACTION
        void send_packet(void*, size_t);
        void receive();
        void logout();
};

#endif
