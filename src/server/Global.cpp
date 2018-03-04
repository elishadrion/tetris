#include "Global.hpp"
#include <vector>

std::vector<Player*> g_connected = std::vector<Player*>();
std::vector<Room*> g_rooms = std::vector<Room*>();
Database* db = new Database();
