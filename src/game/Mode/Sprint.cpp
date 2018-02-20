/*
Groupe 2 : 3V-CUBE

Sprint.hpp
*/

#include "Sprint.hpp"


Sprint::Sprint(): Mode(){

	init_game();
	start();

}

Sprint::~Sprint(){


	delete grid;
	delete display;
}



void Sprint::start(){
	/*	
	Cette fonction lance une partie de type sprint.
	On gagne quand on fait 40 lignes complètes.		
	*/
	 
	init_game();
	bool gridOverload = false;	
	int line_complete =0;
	
	std::thread thread_joueur (player_choice_in_game,grid); // Thread pour les inputs du joueur
	
	while(not(gridOverload) and not(line_complete == 40)){
		
		grid->tetriminos_generator();						
		line_complete += tetriminos_dropping();	
		gridOverload = grid->is_overload();
				
		delete grid->get_tetriminos();
	}
	thread_joueur.detach();			
}
