#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "Player.hpp"
#include "Room.hpp"
#include "Database.hpp"

extern std::vector<Player*> g_connected;
extern std::vector<Room*> g_rooms;
extern Database* db;

#endif
