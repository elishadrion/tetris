#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <cstdlib>
#include <iostream>

#include "Player.hpp"
#include "include/json.hpp"

#define PLAYERS_PATH "server/assets/"

class PlayerManager {
    std::vector<Player*> connected;
public:
    PlayerManager();
    Player signUp();
    Player* signIn(std::string, std::string, int);
    virtual ~PlayerManager();
};

#endif /* PLAYERMANAGER_HPP */
