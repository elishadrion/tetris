/*
Groupe 2 : 3V-CUBE

vsGUI.hpp
*/
#ifndef __GUI__HPP__
#define __GUI__HPP__
#include <ncurses.h>
#include <string.h>
#include "../Game_system/Grid.hpp"


class vsGUI{

	private:
		
		WINDOW * BOX_GRID_PLAYER;
		WINDOW * BOX_GRID_OTHER;

		WINDOW * BOX_NEXT_TETRIMINOS;
		WINDOW * BOX_HOLD_TETRIMINOS;

		WINDOW * BOX_NEXT_TETRIMINOS_OTHER;
		WINDOW * BOX_HOLD_TETRIMINOS_OTHER;



	public:
		
		vsGUI();
		~vsGUI();

		void init_colors();
		void init_main_game_GUI();
		
   		void update_main_game_GUI(Grid * grid, Grid * other_grid);
   		void update_hold_tetriminos_GUI(Tetriminos * hold_tetriminos);
   		void update_next_tetriminos_GUI(Tetriminos * next_tetriminos, Tetriminos * next_tetriminos_other);
   		
   		void erase_hold_tetriminos_GUI();
   		void erase_next_tetriminos_GUI();
   		void erase_hold_tetriminos_other_GUI();
   		void update_hold_tetriminos_other_GUI(Tetriminos* hold_tetriminos_other);
   		

   		


};

#endif