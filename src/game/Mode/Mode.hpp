/*
Groupe 2 : 3V-CUBE

Mode.hpp
*/

#ifndef __GAME__HPP__
#define __GAME__HPP__

#include <unistd.h>
#include <string.h>
#include <thread>
//#include "../GUI/GUI.hpp"
#include "../GUI/vsGUI.hpp"


void player_choice_in_game(Grid * grid);
void update_gui(Grid * grid);

extern vsGUI *display;
class Mode{

	protected:
		
		Grid * grid;
		
		
	public:
		
		Mode();
		virtual ~Mode(){};	
    	virtual void init_game();
		virtual int tetriminos_dropping();
		virtual void start() =0;

};

#endif
