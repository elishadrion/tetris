/*
Groupe 2 : 3V-CUBE

Game.cpp
*/

#include "Game.hpp"
#include "Grid.hpp"



void player_choice(Grid * grid){

	int ch;

	while(1){
		
		ch = getch();
		
		if      (ch == KEY_RIGHT) {grid->current_tetriminos_move_right();}
		else if (ch == KEY_LEFT)  {grid->current_tetriminos_move_left();}
		else if (ch ==  'd')      {grid->current_tetriminos_turn_right();}
		else if (ch ==  'q')      {grid->current_tetriminos_turn_left();}
		else if (ch ==  KEY_DOWN) {grid->current_tetriminos_hard_drop();}
		else if (ch ==  'h')      {grid->set_current_tetriminos_hold();}

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

	myGUI->init_window_GUI();

}

int Game::tetriminos_dropping(Tetriminos * newTetriminos){
	/*
	Cette fonction permet la chute du tétriminos
	et vérifie la grille du jeu.
		:return int: lineCOmplete

	*/

	bool tetriminosIsFix = false;
	int line_complete = 0;	// Compteur de ligne complète

	myGUI->update_next_tetriminos_GUI(grid);
	myGUI->update_grid_GUI(grid);  // On update l'affichage de la grille
	usleep(_acceleration);  

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
		
		myGUI->update_grid_GUI(grid);
		usleep(_acceleration);

	}

	return line_complete;
}

Tetriminos * Game::tetriminos_generator(){
	/*	
	Cette fonction permet la chute du tétriminos
	et vérifie la grille du jeu.
		:return newTetriminos: Tetriminos*
	*/

	int color = rand()%7;
	Tetriminos * newTetriminos;

	if(grid->get_hold_tetriminos() == nullptr){
		newTetriminos = new Tetriminos(color);
	}
	else{

		newTetriminos = grid->get_hold_tetriminos();
	}

	if(grid->has_tetriminos_hold()){
		grid->set_state_tetriminos_hold(false);
	}

	grid->set_tetriminos(newTetriminos);

	color = rand()%7;
	Tetriminos * nextNewTetriminos = new Tetriminos(color);
	grid->set_hold_tetriminos(nextNewTetriminos);

	return newTetriminos;
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
	std::thread thread_joueur (player_choice,grid); // Thread pour les inputs du joueur

	while(not(gridOverload)){

		Tetriminos * newTetriminos = tetriminos_generator();						
		line_complete += tetriminos_dropping(newTetriminos);		
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
	std::thread thread_joueur (player_choice,grid); // Thread pour les inputs du joueur
	
	while(not(gridOverload) and not(line_complete == 40)){

		Tetriminos * newTetriminos = tetriminos_generator();						
		line_complete += tetriminos_dropping(newTetriminos);		
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
	std::thread thread_joueur (player_choice,grid); // Thread pour les inputs du joueur

	
	while(not(gridOverload) and not(line_complete == 200)){

		Tetriminos * newTetriminos = tetriminos_generator();						
		line_complete += tetriminos_dropping(newTetriminos);		
		gridOverload = grid->is_overload();

		// Chaque 10 lignes complètes, l'accélération augmente. 
		if (line_complete!=0 and  line_complete%10 == 0){_acceleration-= 10000 ;}
				
		delete grid->get_tetriminos();	 
	}
	thread_joueur.detach();			
}
