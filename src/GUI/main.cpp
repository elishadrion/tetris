#include "Board.hpp"
#include "Mode/Classic.hpp"

Board* display_game;
int main() {
	display_game = new Board(800, 600);
	Mode* game = new Classic(0);
	game->init_game(true);
	delete display_game;
	return 0;
}