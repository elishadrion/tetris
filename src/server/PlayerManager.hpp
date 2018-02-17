#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>
class Player;
#include "Player.hpp"
#include "../dependencies/json.hpp"
#include "../common/Packet.hpp"

#define PLAYERS_DB "server/assets/players.json"

namespace PlayerManager {
    extern std::vector<Player*> _connected;

    bool player_connected(const std::string&);
    bool player_existing(const std::string&);
    Player* signup(std::string, std::string, int);
    Player* login(std::string, std::string, int);
    void logout(Player*);
}

#endif /* PLAYERMANAGER_HPP */
