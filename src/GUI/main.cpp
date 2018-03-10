#include "Board.hpp"
#include "Mode/Classic.hpp"

Board* display_game;
int main() {
	Mode* game = new Classic(10);
	display_game = new Board(800, 600, game->get_grid());
	game->init_game(true);
	display_game->start();
	//display_game->start();
	delete display_game;
	return 0;
}