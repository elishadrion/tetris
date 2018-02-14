/*
Groupe 2 : 3V-CUBE

main.cpp
*/


#include "Game.hpp"
#include <unistd.h>


int main(){


	Game * game = new Game();
	game->start_marathon_game();
	
	delete game;

	return 0;

}