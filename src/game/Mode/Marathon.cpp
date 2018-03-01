/*
Groupe 2 : 3V-CUBE

Marathon.cpp
*/

#include "Marathon.hpp"

Marathon::Marathon(unsigned seed): Mode(true,seed){

}


Marathon::~Marathon(){


	delete grid;
	
}

void Vs::init_game(bool is_player){
	 // Graine du randomizer
	std::thread t(&Vs::start,this,grid);
	t.detach();
	

	if(is_player){
		gui->init_main_game_GUI();
		usleep(2000);
		std::thread v(&Vs::update_gui, this, grid); // Thread pour les inputs du joueur
		v.detach();
	}
}


void Marathon::start(){
	/*	
	Cette fonction lance une partie de type marathon.
	On gagne quand on fait 200 lignes complètes. On augmente la 
	difficulté chaque 10 lignes complètes.		
	*/
	 
	
	bool gridOverload = false;	
	int line_complete = 0;

	while(!g_is_finished and not(gridOverload) and not(line_complete == 200)){

		grid->tetriminos_generator();						
		line_complete += tetriminos_dropping();	
		gridOverload = grid->is_overload();
				
		// Chaque 10 lignes complètes, l'accélération augmente. 
		if (line_complete!=0 and  line_complete%10 == 0){

			grid->set_acceleration(grid->get_acceleration() - 10000);
		}
		
		delete grid->get_tetriminos();	 
	}

	g_is_finished = true;

}