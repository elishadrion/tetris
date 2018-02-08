/*
Groupe 2 : 3V-CUBE

Game.cpp
*/

#include "Game.hpp"

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

void Game::start_Game(){

	 
	srand(time(NULL)); // Graine du randomizer

	 
	myGUI->window_grid_GUI(); // On affiche la première fenêtre.
	noecho();    // On cache les inputs du terminal.
	keypad(stdscr, TRUE);

	

	std::thread thread_joueur (player_choice,grid); // Thread pour les inputs du joueur


	bool gridOverload = false;
	while(not(gridOverload)){

		Tetriminos * newTetriminos = new Tetriminos(template_tetriminos[rand()%(7)]);
		
		grid->setTetriminos(newTetriminos);
		
		
		myGUI->update_grid_GUI(grid);
		sleep(0.2);
		
		bool tetriminosIsFix = false;
		while(not(tetriminosIsFix)){
		
			
			newTetriminos->drop();
			grid->check_lines();
			myGUI->update_grid_GUI(grid);

			if(grid->isReachingFloor()){
				gridOverload = grid->fix_block(); 
				tetriminosIsFix = true;
			}

			usleep(300000);

		}
		
		
		delete newTetriminos;
	
	

	 
	}

	thread_joueur.detach();



		
    		
    		
    		
			
			
}