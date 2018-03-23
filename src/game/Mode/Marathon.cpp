/*
Groupe 2 : 3V-CUBE

Marathon.cpp
*/

#include "Marathon.hpp"

Marathon::Marathon(unsigned seed): Mode(true,seed){

}


Marathon::~Marathon(){


	delete grid;
	//delete stopper;
	
}

void Marathon::init_game(bool is_player){
	 // Graine du randomizer
	std::thread t(&Marathon::start,this,grid, grid, stopper);
	t.detach();
	
}


void Marathon::start(Grid * grid,Grid * grid_other ,Stopper_Thread* stopper){
	/*	
	Cette fonction lance une partie de type marathon.
	On gagne quand on fait 200 lignes complètes. On augmente la 
	difficulté chaque 10 lignes complètes.		
	*/
	 
	
	bool gridOverload = false;	
	int line_complete = 0;

	while(!stopper->game_is_finish() and  not(gridOverload) and not(line_complete == 200)){

		grid->tetriminos_generator();						
		line_complete += tetriminos_dropping(grid);	
		gridOverload = grid->is_overload();
				
		// Chaque 10 lignes complètes, l'accélération augmente. 
		if (line_complete!=0 and  line_complete%10 == 0){

			grid->set_acceleration(grid->get_acceleration() - 10000);
		}
		
			 
	}

	
	stopper->game_finish();
}

bool Marathon::is_winner(){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	 
	if(grid->get_line_complete() == 200){return true;}
	return false;
}