#include "Room.hpp"

Room::Room(bool is_solo) {
	_is_solo = is_solo;
}

Room::~Room() {
	delete _games[0];
	if (!_is_solo)
		delete _games[1];
}

bool Room::is_solo() {
	return _is_solo;
}
