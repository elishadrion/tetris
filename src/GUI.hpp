/*
Groupe 2 : 3V-CUBE

GUI.hpp
*/
#ifndef __GUI__HPP__
#define __GUI__HPP__
#include <ncurses.h>
#include <string.h>
#include "Grid.hpp"


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
   		void window_grid_GUI();
   		void init_login_GUI();


   		void update_grid_GUI(Grid * grid);
   		void update_hold_tetriminos_GUI(Grid * grid);
   		void update_next_tetriminos_GUI(Grid * grid);
   		void erase_hold_tetriminos_GUI();
   		void erase_next_tetriminos_GUI();
   		void translate_data(char*);



};

#endif