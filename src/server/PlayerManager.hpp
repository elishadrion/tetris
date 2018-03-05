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
#include "../game/Mode/Classic.hpp"
#include "../game/Mode/Marathon.hpp"
#include "../game/Mode/Sprint.hpp"
#include "../game/Mode/Vs.hpp"
#include "../game/CLI/Game_CLI.hpp"


class Room;
#include "Room.hpp"
class Player;
#include "Player.hpp"
#include "Global.hpp"

namespace PlayerManager {
    //Gestion du joueur
    bool player_connected(const std::string&);
    Player* find_player(char*);
    Player* signup(std::string, std::string, int);
    Player* login(std::string, std::string, int);
    void manage_new_player(Player*, int);
    void logout(Player*);
    //Gestion des parties
    Room* create_new_room(int);
    Room* find_available_room(int);
    void broadcast_game_ready(Room*);
    void start_game(Room*,int); 
    void info_game(Room * room, Stopper_Thread * stopper);
}

#endif /* PLAYERMANAGER_HPP */
