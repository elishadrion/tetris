/*
Groupe 2 : 3V-CUBE

Mode.hpp
*/

#ifndef __GAME__HPP__
#define __GAME__HPP__

class Mode;

#include <unistd.h>
#include <string.h>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include "../CLI/Game_CLI.hpp"
#include "../../client/GUI/Board.hpp"
#include "../Game_system/Grid.hpp"
#include "../../common/Packet.hpp"
#include "../../common/Stopper_Thread.hpp"



extern Game_CLI* display_game;
extern Board* display_game_gui;


class Mode {

	protected:
		
		Grid * grid;
		Grid * _other_grid;
		Stopper_Thread * stopper;
		
	public:
		
		Mode(bool,unsigned);
		virtual ~Mode(){};	
    	virtual void init_game(bool is_player)=0;
    	virtual Grid* get_grid(){return grid;}
    	int get_score_player(int);
    	virtual Grid* get_other_grid() {return _other_grid;}
    	void update_gui_multi(Grid *, Grid*,Stopper_Thread*);
    	void update_gui_solo(Grid *,  Stopper_Thread* );
		virtual int tetriminos_dropping(Grid *);
		void move_tetriminos_first_grid(unsigned);
		void move_tetriminos_second_grid(unsigned);
		virtual void start(Grid*, Grid*, Stopper_Thread*)=0;
		Stopper_Thread * get_stopper(){return stopper;}
	
		

};

#endif
