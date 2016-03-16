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
    PlayerConnect(int sockfd, Player*);
    inline void updateSockfd(int sock) {_sockfd = sock;}
    void sendPacket(Packet::packet*, size_t);
    void recvLoop();
    void logout();
    void setPlayerInGame(PlayerInGame*);
    void removePlayerInGame(PlayerInGame*);

    virtual ~PlayerConnect() { close(_sockfd); }
};

#endif /* PLAYERCONNECT_HPP */
