/*
Groupe 2 : 3V-CUBE

Classic.cpp
*/

#include "Classic.hpp"


Classic::Classic(): Mode() {

	init_game();
	start();

}

Classic::~Classic(){


	delete grid;
	delete display;
}


void Classic::start(){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	 
	
	int line_complete = 0;
	bool gridOverload = false;	
	
	
	std::thread thread_joueur (player_choice_in_game,grid); // Thread pour les inputs du joueur

	while(not(gridOverload)){

		grid->tetriminos_generator();						
		line_complete += tetriminos_dropping();		
		gridOverload = grid->is_overload();
		
		delete grid->get_tetriminos();

		// std::string s =  std::to_string(line_complete);
		// char const *message = s.c_str();
		// mvprintw(0, 0, "%d",line_complete);
		
	}
	thread_joueur.detach();			
}

