#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>

class Player;
#include "Player.hpp"
#include "include/json.hpp"
#include "common/Packet.hpp"

#define PLAYERS_DB "server/assets/players.json"

namespace PlayerManager {
    extern std::vector<Player*> _connected;
    extern std::vector<Player*> _players;

    void sendRanking(Player*);
    void loadPlayers();
    void savePlayers();
    Player* findPlayerByName(std::string);
    Player* signUp(std::string, std::string, int);
    Player* logIn(std::string, std::string, int);
    void logOut(Player*);
}

#endif /* PLAYERMANAGER_HPP */
