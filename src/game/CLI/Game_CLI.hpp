/*
Groupe 2 : 3V-CUBE

vsGUI.hpp
*/
#ifndef __GAMECLI__HPP__
#define __GAMECLI__HPP__
#include <ncurses.h>
#include <string.h>
#include "../Game_system/Grid.hpp"

class Game_CLI {

	private:
		
		WINDOW * BOX_GRID_PLAYER;
		WINDOW * BOX_GRID_OTHER;

		WINDOW * BOX_NEXT_TETRIMINOS;
		WINDOW * BOX_HOLD_TETRIMINOS;

		WINDOW * BOX_NEXT_TETRIMINOS_OTHER;
		WINDOW * BOX_HOLD_TETRIMINOS_OTHER;


	public:
		
		Game_CLI();
		 ~Game_CLI();

		 void init_colors();
		 void init_main_game_solo_GUI();
		 void init_main_game_multi_GUI();

		 void erase_hold_tetriminos_multi_GUI();
		 void erase_next_tetriminos_multi_GUI();
		 void erase_next_tetriminos_other_multi_GUI();
		 void erase_hold_tetriminos_other_GUI();   		
   		 void erase_next_tetriminos_solo_GUI();
   		 void erase_hold_tetriminos_solo_GUI();
   		 
		
   		 void update_main_game_multi_GUI(Grid * grid, Grid * other_grid);
   		 void update_main_game_solo_GUI(Grid * grid);   	

   		 void update_next_tetriminos_multi_GUI(Tetriminos * next_tetriminos, Tetriminos * next_tetriminos_other);   
   		 void update_next_tetriminos_solo_GUI(Tetriminos * next_tetriminos);	

   		 void update_hold_tetriminos_other_GUI(Tetriminos* hold_tetriminos_other);
   		 void update_hold_tetriminos_solo_GUI(Tetriminos * hold_tetriminos);   		
   		 void update_hold_tetriminos_multi_GUI(Tetriminos * hold_tetriminos);
   	



};

#endif