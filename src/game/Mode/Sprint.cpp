/*
Groupe 2 : 3V-CUBE

Sprint.hpp
*/

#include "Sprint.hpp"


Sprint::Sprint(unsigned seed): Mode(true,seed){

}

Sprint::~Sprint(){


	delete grid;
	
}


void Sprint::init_game(bool is_player){
	 // Graine du randomizer
	std::thread t(&Sprint::start,this,grid, grid, stopper);
	t.detach();
	

	if(is_player){
		display_game->init_main_game_GUI(0);
		usleep(2000);
		std::thread v(&Sprint::update_gui_solo, this, grid, stopper); // Thread pour les inputs du joueur
		v.detach();
	}
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
				
		delete grid->get_tetriminos();
	}
	stopper->game_finish();		
}
