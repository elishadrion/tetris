#ifndef ROOM_HPP
#define ROOM_HPP
class Player;
#include "Player.hpp"
#include "../game/Mode/Mode.hpp"

class Room {

	private:
		
		unsigned _max_size;
		unsigned _size;
		Player** _players;
		Mode* game;
		
	public:
		Room(unsigned);
		~Room();
		
		inline bool is_full() { return _size == _max_size;}
		inline unsigned get_max_size()const{return _max_size;}
		inline unsigned get_size()const{return _size;}
		void set_mode(Mode* mode){game = mode;}
		Mode* get_mode(){return game;}
		Player* get_player(unsigned i) {return _players[i];}
		void add_player(Player* player);
		void move_tetriminos(Player* player, unsigned movej) {
			if (_players[0] == player) {game->move_tetriminos_first_grid(movej);}
			else {game->move_tetriminos_second_grid(movej);}
		}
		
		

};



#endif