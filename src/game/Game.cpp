/*
Groupe 2 : 3V-CUBE

Game.cpp
*/

#include "Game.hpp"
#include "Grid.hpp"



void player_choice_in_game(Grid * grid){

	int ch;

	while(1){
		
		ch = getch();
		
		if      (ch == KEY_RIGHT) {grid->current_tetriminos_move_right();}
		else if (ch == KEY_LEFT)  {grid->current_tetriminos_move_left();}
		else if (ch ==  'd')      {grid->current_tetriminos_turn_right();}
		else if (ch ==  'q')      {grid->current_tetriminos_turn_left();}
		else if (ch ==  'z')      {grid->current_tetriminos_hard_drop();}
		else if (ch ==  'h')      {grid->set_current_tetriminos_hold();}
		else if (ch ==  KEY_DOWN) {grid->set_acceleration_quick(); }
			

	}
}



Game::Game(): grid(new Grid()) , myGUI(new GUI()) {}

Game::~Game(){

	delete grid;
	delete myGUI;
}	

void Game::init(){

	srand(time(NULL)); // Graine du randomizer

}

void Game::start(){

	myGUI->init_menu_GUI();

}

int Game::tetriminos_dropping(){
	/*
	Cette fonction permet la chute du tétriminos
	et vérifie la grille du jeu.
		:return int: lineCOmplete

	*/

	bool tetriminosIsFix = false;
	int line_complete = 0;	// Compteur de ligne complète
	
	
	
	myGUI->update_grid_GUI(grid);  // On update l'affichage de la grille
	myGUI->update_next_tetriminos_GUI(grid);

	if(grid->get_acceleration()==87654){grid->set_acceleration(300000);}
	usleep(grid->get_acceleration());  

	while(not(tetriminosIsFix)){ 
		
		/*
		On essaye de faire descendre le tétriminos et s'il ne peut plus alors
		on le disloque et on recré un nouveau tétriminos.
		*/

		if(grid->tetriminos_try_drop() == false){
			grid->fix_block();
			line_complete =  grid->check_lines();
			tetriminosIsFix = true;
		}
		if(not(grid->has_tetriminos_hold())){ 

			myGUI->erase_hold_tetriminos_GUI();
		}else{

			myGUI->update_hold_tetriminos_GUI(grid);
		}
		grid->grid_to_char();
		myGUI->update_grid_GUI(grid);
		usleep(grid->get_acceleration());

	}

	
	return line_complete;
}


void Game::start_classic_game(){
	/*	
	Cette fonction lance une partie classique de tetris.
	Sans objectif, on perd quand un tétriminos est hors de la grille.		
	*/
	 
	init();	
	int line_complete = 0;
	bool gridOverload = false;	

	myGUI->window_grid_GUI(); // On affiche la première fenêtre.	
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


void Game::start_sprint_game(){
	/*	
	Cette fonction lance une partie de type sprint.
	On gagne quand on fait 40 lignes complètes.		
	*/
	 
	init();
	bool gridOverload = false;	
	int line_complete =0;
	 
	myGUI->window_grid_GUI(); // On affiche la première fenêtre.	
	std::thread thread_joueur (player_choice_in_game,grid); // Thread pour les inputs du joueur
	
	while(not(gridOverload) and not(line_complete == 40)){
		
		grid->tetriminos_generator();						
		line_complete += tetriminos_dropping();	
		gridOverload = grid->is_overload();
				
		delete grid->get_tetriminos();
	}
	thread_joueur.detach();			
}


void Game::start_marathon_game(){
	/*	
	Cette fonction lance une partie de type marathon.
	On gagne quand on fait 200 lignes complètes. On augmenente la 
	difficulté chaque 10 lignes complètes.		
	*/
	 
	init();
	bool gridOverload = false;	
	int line_complete =0;

	myGUI->window_grid_GUI(); // On affiche la première fenêtre.	
	std::thread thread_joueur (player_choice_in_game,grid); // Thread pour les inputs du joueur

			
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
	thread_joueur.detach();	


}


