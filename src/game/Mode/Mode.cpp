/*
Groupe 2 : 3V-CUBE

Mode.cpp
*/

#include "Mode.hpp"
#include "../Game_system/Grid.hpp"


void player_choice_in_game(Grid * grid){

	int ch;

	while(1){
		
		ch = getch();
		
		if      (ch == KEY_RIGHT) {grid->current_tetriminos_move_right();}
		else if (ch == KEY_LEFT)  {grid->current_tetriminos_move_left();}
		else if (ch == 'd')       {grid->current_tetriminos_turn_right();}
		else if (ch == 'q')       {grid->current_tetriminos_turn_left();}
		else if (ch == 'z')       {grid->current_tetriminos_hard_drop();}
		else if (ch == 'h')       {grid->set_current_tetriminos_hold();}
		else if (ch ==  KEY_DOWN) {grid->set_acceleration_quick();}
			

	}
}


void update_gui(Grid * grid){

	display->update_main_game_GUI(grid);  // On update l'affichage de la grille
	
	while(1){

		
		display->update_next_tetriminos_GUI( grid->get_next_tetriminos());

		if(not(grid->has_tetriminos_hold())){ 

			display->erase_hold_tetriminos_GUI();
		}
		else{

			display->update_hold_tetriminos_GUI(grid->get_hold_tetriminos());
		}
		
		display->update_main_game_GUI(grid);
		usleep(100000);





	}
}




Mode::Mode(): grid(new Grid())  {


}


void Mode::init_game(){

	srand(time(NULL)); // Graine du randomizer
	display->init_main_game_GUI(); // On affiche la première fenêtre.	

}

int Mode::tetriminos_dropping(){
	/*
	Cette fonction permet la chute du tétriminos
	et vérifie la grille du jeu.
		:return int: lineCOmplete

	*/
	
	bool tetriminosIsFix = false;
	int line_complete = 0;	// Compteur de ligne complète	
	
	if(grid->get_acceleration()==87654)
		grid->set_acceleration(300000);

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

		usleep(grid->get_acceleration());

	}
	
	return line_complete;
}






