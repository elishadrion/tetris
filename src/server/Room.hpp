#ifndef ROOM_HPP
#define ROOM_HPP
#include "User.hpp"
#include "../game/Game.hpp"

class Room {

	private:
		bool _is_solo;
		User* _players[2];
		Game* _games[2];
		
	public:
		Room(bool);
		~Room();
		bool is_solo();
		

};


#endif
