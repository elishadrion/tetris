/*
Groupe 2 : 3V-CUBE

main.cpp
*/


#include "./Mode/Classic.hpp"
#include "./Mode/Marathon.hpp"
#include "./Mode/Sprint.hpp"
#include <unistd.h>
#include "./GUI/GUI.hpp"
#include "./GUI/vsGUI.hpp"

vsGUI * display;

int main(){


	// Game * game = new Game();
	// game->start_classic_game();

	display = new vsGUI();
	Mode * game = new Marathon();
	
	delete game;

	

	return 0;

}