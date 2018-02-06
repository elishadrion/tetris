#include "Block.hpp"
#include "Tetriminos.hpp"
#include "grid.hpp"
#include "Game.hpp"
#include <unistd.h>
#include <iostream>





int main(){

	Game * game = new Game();
	game->start_Game();
	
	delete game;

	//

	



	return 0;

}