/*
Groupe 2 : 3V-CUBE

Mode.cpp
*/
#include "Mode.hpp"
bool g_is_finished = false;

// void update_gui(Grid * grid){

// 	gui->update_main_game_GUI(grid);  // On update l'affichage de la grille
// 	while(1){
// 		gui->update_next_tetriminos_GUI( grid->get_next_tetriminos());

// 		if(not(grid->has_tetriminos_hold())){ 

// 			gui->erase_hold_tetriminos_GUI();
// 		}
// 		else{

// 			gui->update_hold_tetriminos_GUI(grid->get_hold_tetriminos());
// 		}
// 		gui->update_main_game_GUI(grid);
// 		usleep(100000);
// 	}
// }



void Mode::update_gui(Grid * grid, Grid * other_grid){

	
	gui->update_main_game_GUI(grid, other_grid);  // On update l'affichage de la grille

	while(!g_is_finished){
		gui->update_next_tetriminos_GUI( grid->get_next_tetriminos(), other_grid->get_next_tetriminos());

		if(not(grid->has_tetriminos_hold())){ 

			gui->erase_hold_tetriminos_GUI();
		}
		else{

			gui->update_hold_tetriminos_GUI(grid->get_hold_tetriminos());
		}

		if(not(other_grid->has_tetriminos_hold())){ 

			gui->erase_hold_tetriminos_other_GUI();
		}
		else{

			gui->update_hold_tetriminos_other_GUI(other_grid->get_hold_tetriminos());
		}


		gui->update_main_game_GUI(grid,other_grid);
		usleep(100000);
	}
}



Mode::Mode(bool is_vs, unsigned seed): grid(new Grid(seed))  {
	if (is_vs) {
		_other_grid = new Grid(seed);

	}
}



int Mode::tetriminos_dropping(Grid * grid){
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


void Mode::move_tetriminos_first_grid(unsigned ID) {
	
	//if(grid==_other_grid){exit0();}

	if      (ID == Packet::MOVE_TETRIMINOS_RIGHT) {
		grid->current_tetriminos_move_right();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_LEFT)  {
		grid->current_tetriminos_move_left();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_TURN_RIGHT)       {
		grid->current_tetriminos_turn_right();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_TURN_LEFT)       {
		grid->current_tetriminos_turn_left();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_HDROP)       {
		grid->current_tetriminos_hard_drop();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_HOLD)       {
		grid->set_current_tetriminos_hold();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_DROP) {
		grid->set_acceleration_quick();
	}
}

void Mode::move_tetriminos_second_grid(unsigned ID) {
	if      (ID == Packet::MOVE_TETRIMINOS_RIGHT) {
		_other_grid->current_tetriminos_move_right();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_LEFT)  {
		_other_grid->current_tetriminos_move_left();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_TURN_RIGHT)       {
		_other_grid->current_tetriminos_turn_right();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_TURN_LEFT)       {
		_other_grid->current_tetriminos_turn_left();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_HDROP)       {
		_other_grid->current_tetriminos_hard_drop();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_HOLD)       {
		_other_grid->set_current_tetriminos_hold();
	}
	else if (ID == Packet::MOVE_TETRIMINOS_DROP) {
		_other_grid->set_acceleration_quick();
	}
}



