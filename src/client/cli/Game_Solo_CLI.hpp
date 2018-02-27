
/*
Groupe 2 : 3V-CUBE

GUI.hpp
*/

#ifndef GAMESOLOCLI__HPP
#define GAMESOLOCLI__HPP
#include <ncurses.h>
#include <string.h>
#include "../../game/Game_system/Grid.hpp"


class Game_Solo_CLI{

	private:

		
		WINDOW * BOX_GRID;
		WINDOW * BOX_NEXT_TETRIMINOS;
		WINDOW * BOX_HOLD_TETRIMINOS;



	public:
		
		Game_Solo_CLI();
		~Game_Solo_CLI();

		void init_colors();
		void init_window_GUI();
		void init_menu_GUI();
   		void init_main_game_GUI();
   		void init_login_GUI();


   		void update_main_game_GUI(Grid * grid);
   		void update_hold_tetriminos_GUI(Tetriminos * hold_tetriminos);
   		void update_next_tetriminos_GUI(Tetriminos * next_tetriminos);
   		void erase_hold_tetriminos_GUI();
   		void erase_next_tetriminos_GUI();
   		

   		


};

#endif