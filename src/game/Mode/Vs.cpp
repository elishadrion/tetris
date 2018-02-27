/*
Groupe 2 : 3V-CUBE

Vs.cpp
*/

#include "Vs.hpp"


Vs::Vs(): Mode(true) {
	

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

	if(is_player){gui->init_main_game_GUI();
		usleep(2000);
		std::thread v (update_gui,grid,_other_grid); // Thread pour les inputs du joueur
		v.detach();
	}
}

void Vs::start(Grid * grid){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	 
	srand(4);
	int line_complete = 0;
	bool gridOverload = false;
	
	
	while(not(gridOverload) ){

		grid->tetriminos_generator();
		

		line_complete += tetriminos_dropping(grid);	
		
		gridOverload = grid->is_overload();		
		
		delete grid->get_tetriminos();
		

		// std::string s =  std::to_string(line_complete);
		// char const *message = s.c_str();
		// mvprintw(0, 0, "%d",line_complete);
		
	}
}


