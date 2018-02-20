/*
Groupe 2 : 3V-CUBE

GUI.hpp
*/
#ifndef __GUI__HPP__
#define __GUI__HPP__
#include <ncurses.h>
#include <string.h>
#include "../Game_system/Grid.hpp"


class GUI{

	private:

		
		WINDOW * BOX_GRID;
		WINDOW * BOX_NEXT_TETRIMINOS;
		WINDOW * BOX_HOLD_TETRIMINOS;



	public:
		
		GUI();
		~GUI();

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