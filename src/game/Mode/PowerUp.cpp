/*
Groupe 2 : 3V-CUBE

Vs.cpp
*/

#include "PowerUp.hpp"


PowerUp::PowerUp(long seed): Mode(true,seed) {}


PowerUp::~PowerUp(){

	delete grid;
	delete _other_grid;
	delete stopper;
	
}

void PowerUp::init_game(bool is_player){
	 // Graine du randomizer
	usleep(20000);
	std::thread t(&PowerUp::start,this,grid,_other_grid ,stopper);
	std::thread t2(&PowerUp::start,this, _other_grid,grid, stopper);
	t.detach();
	t2.detach();
}

void PowerUp::start(Grid * grid, Grid * other_grid , Stopper_Thread* stopper){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	 
	int line_complete = 0;
	bool gridOverload = false;	
	usleep(30000);
	
	while(!stopper->game_is_finish() and !gridOverload ){

		grid->tetriminos_generator();
		line_complete = tetriminos_dropping(grid);
		grid->active_bonus(other_grid);
		if(line_complete>=2){other_grid->add_line(line_complete);}		
		gridOverload = grid->is_overload();				
		
	}
	
	stopper->game_finish();
}

bool PowerUp::is_winner(){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	
	if(_other_grid->is_overload()){ return true;}
	return false;
}



