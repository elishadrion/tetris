/*
Groupe 2 : 3V-CUBE

Sprint.hpp
*/

#include "Sprint.hpp"


Sprint::Sprint(long seed): Mode(true,seed){

}

Sprint::~Sprint(){


	delete grid;
	delete stopper;
	
}


void Sprint::init_game(bool is_player){
	 // Graine du randomizer
	usleep(20000);
	std::thread t(&Sprint::start,this,grid, grid, stopper);
	t.detach();

}




void Sprint::start(Grid * grid,Grid * grid_other ,Stopper_Thread* stopper){
	/*	
	Cette fonction lance une partie de type sprint.
	On gagne quand on fait 40 lignes complètes.		
	*/
	 

	bool gridOverload = false;	
	int line_complete =0;

	
	while(!stopper->game_is_finish() and not(gridOverload) and not(line_complete == 40)){
		
		grid->tetriminos_generator();						
		line_complete += tetriminos_dropping(grid);	
		gridOverload = grid->is_overload();
				
	}
	
	stopper->game_finish();		
}

bool Sprint::is_winner(){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	 
	if(grid->get_line_complete() == 40){ return true;}
	return false;
}