#ifndef PLAYERCONNECT_HPP
#define	PLAYERCONNECT_HPP

class Player;
class PlayerConnect;
#include "Player.hpp"
#include "PlayerManager.hpp"
#include "../common/Packet.hpp"
#include "PacketManager.hpp"

class PlayerConnect {
    int _sockfd;
    Player* _player;

    public:
        #ifndef PLAYERCONNECT_PACKET_THREAD_SAFE
        #define PLAYERCONNECT_PACKET_THREAD_SAFE
        pthread_mutex_t packetStackMutex = PTHREAD_MUTEX_INITIALIZER;
        pthread_cond_t packetStackCond = PTHREAD_COND_INITIALIZER;
        std::vector<void*> packetStack;
        #endif
        
        PlayerConnect(int sockfd, Player*);
        inline void set_sockfd(int sock) {_sockfd = sock;}
        void send_packet(Packet::packet*, size_t);
        void receive();
        void logout();
        Player* get_player_ptr() const {return _player;};
        virtual ~PlayerConnect() { close(_sockfd); }
};

#endif /* PLAYERCONNECT_HPP */
