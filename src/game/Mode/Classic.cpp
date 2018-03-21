/*
Groupe 2 : 3V-CUBE

Classic.cpp
*/

#include "Classic.hpp"


Classic::Classic(unsigned seed): Mode(false,seed) {

	

}

Classic::~Classic(){

	delete grid;
	delete stopper;
}

void Classic::init_game(bool is_player){
	 // Graine du randomizer
	std::thread t(&Classic::start,this,grid, grid, stopper);
	t.detach();
	


}

void Classic::start(Grid * grid,Grid * grid_other ,Stopper_Thread* stopper){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	 
	
	int line_complete = 0;
	bool gridOverload = false;	
	
	

	while(!stopper->game_is_finish() and not(gridOverload)){

		grid->tetriminos_generator();						
		line_complete += tetriminos_dropping(grid);		
		gridOverload = grid->is_overload();
		
	
		
	}
	stopper->game_finish();
			
}

