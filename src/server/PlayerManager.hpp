#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

#include "../dependencies/json.hpp"
#include "../dependencies/CSVparser/CSVparser.hpp"
#include "../common/Packet.hpp"
#include "../common/Random.hpp"

#include "../game/Mode/Vs.hpp"
#include "../game/GUI/vsGUI.hpp"

class Room;
#include "Room.hpp"
class Player;
#include "Player.hpp"
#include "Global.hpp"

namespace PlayerManager {
    //Gestion du joueur
    bool player_connected(const std::string&);
    bool player_existing(const std::string&);
    Player* find_player(int);
    Player* signup(std::string, std::string, int);
    Player* login(std::string, std::string, int);
    void manage_new_player(Player*);
    void logout(Player*);
    //Gestion des parties
    Room* create_new_room();
    Room* find_available_room();
    void broadcast_game_ready(Room*);
    void start_game(Room*); 
}

#endif /* PLAYERMANAGER_HPP */
