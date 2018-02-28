#include "Room.hpp"

Room::Room(unsigned max): _size(0) {
	srand(time(NULL));
	_seed = rand();
	_players = new Player*[max];
	_max_size = max;
}

Room::~Room() {
	delete[] _players;
}

void Room::add_player(Player* player) {_players[_size]=player;_size++; player->set_room(this);}