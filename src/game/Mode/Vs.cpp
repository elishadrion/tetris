/*
Groupe 2 : 3V-CUBE

Vs.cpp
*/

#include "Vs.hpp"


Vs::Vs(unsigned seed): Mode(true,seed) {
	

}


Vs::~Vs(){

	delete grid;
	delete _other_grid;
	
}

void Vs::init_game(bool is_player){
	 // Graine du randomizer
	std::thread t(&Vs::start,this,grid);
	std::thread t2(&Vs::start,this, _other_grid);
	t.detach();
	t2.detach();

	if(is_player){
		gui->init_main_game_GUI();
		usleep(2000);
		std::thread v(&Vs::update_gui, this, grid,_other_grid); // Thread pour les inputs du joueur
		v.detach();
	}
}

void Vs::start(Grid * grid){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	 
	int line_complete = 0;
	bool gridOverload = false;	
	
	while(!g_is_finished and !gridOverload ){

		grid->tetriminos_generator();
		line_complete += tetriminos_dropping(grid);		
		gridOverload = grid->is_overload();		
		
		delete grid->get_tetriminos();
		
	}

	g_is_finished = true;
}


