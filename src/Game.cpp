/*
Groupe 2 : 3V-CUBE

Game.cpp
*/

#include "Game.hpp"
#include<iostream>

#include "Grid.hpp"


#include <mutex>
std::mutex mtx; 



void player_choice(Grid * grid){
	int ch;



	while(1){
		
		ch = getch();
		
		if (ch == KEY_RIGHT) {

			grid->currentTetriminosMoveRight();
		}
		else if (ch == KEY_LEFT) {
			
			grid->currentTetriminosMoveLeft();
		}
		else if(ch ==  'd'){

			grid->currentTetriminosTurnRight();

		}
		else if(ch ==  'q'){

			grid->currentTetriminosTurnLeft();
		}

		else if(ch ==  KEY_DOWN){
			

			grid->currentTetriminosHardDrop();

					
			
		}

		

	}
}

Game::Game(){

	grid = new Grid();
	myGUI = new GUI(); 

}

Game::~Game(){

	delete grid;
	delete myGUI;
}	

void Game::start(){

	myGUI->init_window_GUI();



}


int Game::tetriminosDropping(Tetriminos * newTetriminos){

	bool tetriminosIsFix = false;
	int lineComplete=0;	

	myGUI->update_grid_GUI(grid);
	usleep(_acceleration);

	while(not(tetriminosIsFix)){
	
		
		
		newTetriminos->drop();
		

		if(grid->isReachingFloor()){
			grid->fix_block();
			lineComplete =  grid->check_lines();
			tetriminosIsFix = true;
		}

		
		myGUI->update_grid_GUI(grid);
		usleep(_acceleration);

	}

	return lineComplete;

}


void Game::init(){

	srand(time(NULL)); // Graine du randomizer

}

void Game::start_classic_Game(){

	 
	init();
	
	int lineComplete =0;
	bool gridOverload = false;
	 
	myGUI->window_grid_GUI(); // On affiche la première fenêtre.
	

	std::thread thread_joueur (player_choice,grid); // Thread pour les inputs du joueur


	
	while(not(gridOverload)){

		Tetriminos * newTetriminos = new Tetriminos(template_tetriminos[rand()%(7)]);
		
		grid->setTetriminos(newTetriminos);
						
		lineComplete += tetriminosDropping(newTetriminos);
		
		gridOverload = grid->isOverload();
		
		delete newTetriminos;

		// std::string s =  std::to_string(lineComplete);
		// char const *message = s.c_str();
		mvprintw(0, 0, "%d",lineComplete);
		refresh();
		
	 
	}

	thread_joueur.detach();

	
			
}


void Game::start_sprint_Game(){

	 
	init();

	bool gridOverload = false;
	
	int lineComplete =0;


	 
	myGUI->window_grid_GUI(); // On affiche la première fenêtre.
	

	std::thread thread_joueur (player_choice,grid); // Thread pour les inputs du joueur

	
	while(not(gridOverload) and not(lineComplete == 40)){

		Tetriminos * newTetriminos = new Tetriminos(template_tetriminos[rand()%(7)]);
		
		grid->setTetriminos(newTetriminos);
						
		lineComplete += tetriminosDropping(newTetriminos);
		
		gridOverload = grid->isOverload();
		
		
		delete newTetriminos;

	 
	}

	thread_joueur.detach();
			
}


void Game::start_marathon_Game(){

	 
	init();

	bool gridOverload = false;
	
	int lineComplete =0;


	 
	myGUI->window_grid_GUI(); // On affiche la première fenêtre.
	

	std::thread thread_joueur (player_choice,grid); // Thread pour les inputs du joueur

	
	while(not(gridOverload) and not(lineComplete == 200)){

		Tetriminos * newTetriminos = new Tetriminos(template_tetriminos[rand()%(7)]);
		
		grid->setTetriminos(newTetriminos);
						
		lineComplete += tetriminosDropping(newTetriminos);
		
		gridOverload = grid->isOverload();

		if (lineComplete!=0 and  lineComplete%20 == 0){_acceleration-= 10000 ;}
		
		
		delete newTetriminos;

	 
	}

	thread_joueur.detach();
			
}
