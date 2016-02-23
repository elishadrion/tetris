#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <cstdlib>
#include <iostream>
#include <algorithm>

#include "Player.hpp"
#include "include/json.hpp"
#include "common/Packet.hpp"

#define PLAYERS_DB "server/assets/players.json"

class PlayerManager {
    std::vector<Player*> connected;
    std::vector<Player*> players;
public:
    PlayerManager();
    std::string getRanking();
    void loadPlayers();
    Player signUp();
    Player* logIn(Packet::loginRequestPacket, int);
    virtual ~PlayerManager();
};

#endif /* PLAYERMANAGER_HPP */
