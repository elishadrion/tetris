/*
Groupe 2 : 3V-CUBE

Mode.hpp
*/

#ifndef __GAME__HPP__
#define __GAME__HPP__

#include <unistd.h>
#include <string.h>
#include <thread>
#include<stdlib.h>
#include<time.h>
//#include "../GUI/GUI.hpp"
#include "../GUI/vsGUI.hpp"
#include "../Game_system/Grid.hpp"
#include "../../common/Packet.hpp"


void update_gui(Grid * grid, Grid * other_grid);
extern vsGUI *gui;

class Mode{

	protected:
		
		Grid * grid;
		Grid * _other_grid;
		
	public:
		
		Mode(bool,unsigned);
		virtual ~Mode(){};	
    	virtual void init_game(bool is_player)=0;
    	virtual Grid* get_grid(){return grid;}
    	virtual Grid* get_other_grid() {return _other_grid;}
		virtual int tetriminos_dropping(Grid *);
		void move_tetriminos_first_grid(unsigned);
		void move_tetriminos_second_grid(unsigned);
		virtual void start(Grid*)=0;
		//virtual void start2(Grid *)=0;
		
		

};

#endif
