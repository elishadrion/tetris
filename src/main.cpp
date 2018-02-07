/*
Groupe 2 : 3V-CUBE

main.cpp
*/


#include "Game.hpp"
#include <unistd.h>


int main(){

	
	initscr(); // première routine à appelé avant d'initialiser un programme.
	Game * game = new Game();
	game->start_Game();
	
	delete game;
	endwin();

	

	



	return 0;

}