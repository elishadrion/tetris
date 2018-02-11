/*
Groupe 2 : 3V-CUBE

Grid.hpp
*/

#ifndef __GRID__HPP__
#define __GRID__HPP__

#include "Tetriminos.hpp"

class Grid{

	private:

		Block ** _grid;
		Tetriminos * _currentTetriminos;
		Tetriminos * _hold_Tetriminos;
		bool hold;

	public:

		Grid();
		~Grid();

		//Getter
		Block get_block(int i, int j);
		Tetriminos * get_tetriminos();
		Tetriminos * get_hold_tetriminos();		
		int get_color_of_tetriminos();
		int get_color_of_block(int i , int k);

		//Setter
		void set_tetriminos(Tetriminos * tetriminos);
		void set_hold_tetriminos(Tetriminos * tetriminos);
		void set_state_tetriminos_hold(bool state);

		bool is_reaching_floor();
		bool is_colliding_right();
		bool is_colliding_left();
		bool is_colliding_rotation(int rotationMat[2][2]);
		bool is_empty(int i, int j);
		bool is_overload();

		void fix_block();
		int  check_lines();		
		bool tetriminos_try_drop();
		bool has_tetriminos_hold();
		

		void current_tetriminos_move_right();
		void current_tetriminos_move_left();
		void current_tetriminos_turn_right();
		void current_tetriminos_turn_left();		
		void current_tetriminos_hard_drop();
		void set_current_tetriminos_hold();


};
#endif