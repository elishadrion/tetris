/*
Groupe 2 : 3V-CUBE

GUI.hpp
*/
#ifndef __GUI__HPP__
#define __GUI__HPP__
#include <ncurses.h>
#include<string.h>
#include "Grid.hpp"


class GUI{

	private:
		WINDOW *boite;


	public:
		GUI();
		~GUI();


		void init_window_GUI();
   		void window_grid_GUI();
   		void update_grid_GUI(Grid * grid);

};

#endif