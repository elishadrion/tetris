/*
Groupe 2 : 3V-CUBE

Vs.cpp
*/

#include "Vs.hpp"


Vs::Vs(unsigned seed): Mode(true,seed) {}


Vs::~Vs(){

	delete grid;
	delete _other_grid;
	
}

void Vs::init_game(bool is_player){
	 // Graine du randomizer
	std::thread t(&Vs::start,this,grid,_other_grid ,stopper);
	std::thread t2(&Vs::start,this, _other_grid,grid, stopper);
	t.detach();
	t2.detach();

	if(is_player){

		display_game->init_main_game_multi_GUI();
		usleep(2000);
		std::thread v(&Vs::update_gui_multi, this, grid,_other_grid, stopper); // Thread pour les inputs du joueur
		v.detach();
	}
}

void Vs::start(Grid * grid,Grid * other_grid , Stopper_Thread* stopper){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	 
	int line_complete = 0;
	bool gridOverload = false;	
	
	while(!stopper->game_is_finish() and !gridOverload ){

		grid->tetriminos_generator();
		line_complete = tetriminos_dropping(grid);
		if(line_complete>=2){other_grid->add_line(line_complete);}		
		gridOverload = grid->is_overload();		
		
		delete grid->get_tetriminos();
		
	}

	stopper->game_finish();
}


