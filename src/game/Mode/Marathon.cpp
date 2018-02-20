/*
Groupe 2 : 3V-CUBE

Marathon.cpp
*/

#include "Marathon.hpp"

Marathon::Marathon(): Mode(){

	init_game();
	start();

}


Marathon::~Marathon(){


	delete grid;
	delete display;
}



void Marathon::start(){
	/*	
	Cette fonction lance une partie de type marathon.
	On gagne quand on fait 200 lignes complètes. On augmente la 
	difficulté chaque 10 lignes complètes.		
	*/
	 
	
	bool gridOverload = false;	
	int line_complete = 0;
	
	std::thread thread_joueur (player_choice_in_game,grid); // Thread pour les inputs du joueur
	std::thread test (update_gui,grid); // Thread pour les inputs du joueur
			
	while(not(gridOverload) and not(line_complete == 200)){

		grid->tetriminos_generator();						
		line_complete += tetriminos_dropping();	
		gridOverload = grid->is_overload();
				
		// Chaque 10 lignes complètes, l'accélération augmente. 
		if (line_complete!=0 and  line_complete%10 == 0){

			grid->set_acceleration(grid->get_acceleration() - 10000);
		}
		
		delete grid->get_tetriminos();	 
	}

	test.detach();
	thread_joueur.detach();


}