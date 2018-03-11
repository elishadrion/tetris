#include "Board.hpp"
#include "Mode/Classic.hpp"
#include "Mode/Vs.hpp"

Board* display_game;
int main() {
	//Mode* game = new Classic(10);
	Mode* game = new Vs(10);
	display_game = new Board(true, 800, 600, game->get_grid(), game->get_other_grid());
	game->init_game(true);
	display_game->start();
	//display_game->start();
	delete display_game;
	return 0;
}