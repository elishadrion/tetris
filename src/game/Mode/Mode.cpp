/*
Groupe 2 : 3V-CUBE

Mode.cpp
*/
#include "Mode.hpp"



Mode::Mode(bool is_vs, unsigned seed): grid(new Grid(seed)), stopper(new Stopper_Thread())  {
	if (is_vs) {
		_other_grid = new Grid(seed);

	}
}

int Mode::get_score_player(int player_nb){
	if(player_nb == 1){return grid->get_score();}
	else if(player_nb ==2){return _other_grid->get_score();}

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



