/*
Groupe 2 : 3V-CUBE

vsGUI.hpp
*/

#ifndef __GAMEMULTICLI__HPP__
#define __GAMEMULTICLI__HPP__
#include <ncurses.h>
#include <string.h>
#include "../../game/Game_system/Grid.hpp"


class Game_Multi_CLI{

	private:
		
		WINDOW * BOX_GRID_PLAYER;
		WINDOW * BOX_GRID_OTHER;

		WINDOW * BOX_NEXT_TETRIMINOS;
		WINDOW * BOX_HOLD_TETRIMINOS;

		WINDOW * BOX_NEXT_TETRIMINOS_OTHER;
		WINDOW * BOX_HOLD_TETRIMINOS_OTHER;

	public:
		
		Game_Multi_CLI();
		~Game_Multi_CLI();

		void init_colors();
		void init_main_game_GUI();
		
   		void update_main_game_GUI(Grid * grid);
   		void update_hold_tetriminos_GUI(Tetriminos * hold_tetriminos);
   		void update_next_tetriminos_GUI(Tetriminos * next_tetriminos);
   		void erase_hold_tetriminos_GUI();
   		void erase_next_tetriminos_GUI();
   		void  update_gui(Grid* grid);
   		


};

#endif