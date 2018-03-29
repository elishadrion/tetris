#include "Room.hpp"

Room::Room(unsigned max): _size(0) ,game(nullptr){
	srand(time(NULL));
	_seed = rand();
	_players = new Player*[max];
	for(int i = 0; i<max;i++){ _players[i] = nullptr;}
	_max_size = max;
}

Room::~Room() {

	delete game;	
	delete[] _players;
}

void Room::add_player(Player* player) {_players[_size]=player;_size++; player->set_room(this);}