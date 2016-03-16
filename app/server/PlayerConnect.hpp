#ifndef PLAYERCONNECT_HPP
#define	PLAYERCONNECT_HPP

class Player;
class PlayerInGame;
class PlayerConnect;
#include "Player.hpp"


class PlayerConnect {
    Player* _player;
    PlayerInGame* _pIG;

    int _sockfd;


    Player* getPlayerPtr();

public:
    PlayerConnect(int sockfd);
    inline void updateSockfd(int a) {_sockfd = a;}
    void sendPacket(Packet::packet*, size_t);
    void recvLoop();
    void logout();
    void removePlayerInGame(PlayerInGame*);

    virtual ~PlayerConnect() { close(_sockfd); }
};

#endif /* PLAYERCONNECT_HPP */
