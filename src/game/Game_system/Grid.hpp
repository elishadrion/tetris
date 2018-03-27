/*
Groupe 2 : 3V-CUBE

Grid.hpp
*/

#ifndef __GRID__HPP__
#define __GRID__HPP__

#include "Tetriminos.hpp"
#include <mutex>
#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <math.h>
#include "../../common/Random.hpp"



class Grid{

	private:

		Block ** _grid;

		Tetriminos * _current_tetriminos;
		Tetriminos * _next_tetriminos;
		Tetriminos * _hold_tetriminos;
		Tetriminos * _ghost_tetriminos;

		Random *_number_generator;

		int _acceleration;
		int _score;
		int _level;
		int _line_complete;
		int _line_stack;


	public:

		Grid(long);
		~Grid();

		//Getter

		Tetriminos * get_tetriminos()const;
		Tetriminos * get_next_tetriminos()const;	
		Tetriminos * get_hold_tetriminos()const;	
		Tetriminos * get_ghost_tetriminos()const;
		int get_color_of_tetriminos()const;
		int get_color_of_block(int i , int j)const;
		int get_acceleration()const;
		int get_score()const;
		int get_level()const;
		int get_line_complete()const;
		Block** get_grid()const;

		//Setter
		void set_tetriminos(Tetriminos * tetriminos);
		void set_hold_tetriminos(Tetriminos * tetriminos);
		void set_next_tetriminos(Tetriminos * tetriminos);
		void set_state_tetriminos_hold(bool state);
		void set_acceleration(int acceleration);
		void set_acceleration_quick();
		void set_grid(Block**);

		bool is_reaching_floor()const;
		bool is_colliding_right()const;
		bool is_colliding_left()const;
		bool is_colliding_rotation(int rotationMat[2][2])const;
		bool is_empty(int i, int j)const;
		bool is_overload()const;

		void fix_block();
		int  check_lines();		
		bool tetriminos_try_drop();
		bool has_tetriminos_hold()const;
		void tetriminos_generator();
		void swap_grid(Grid*);
		void destroy_block();

		void current_tetriminos_move_right();
		void current_tetriminos_move_left();
		void current_tetriminos_turn_right();
		void current_tetriminos_turn_left();		
		void current_tetriminos_hard_drop();
		void set_current_tetriminos_hold();


		void update_score_level();
		void add_line(int line);
		void add_line_complete(int lines);
		void ghost();





	
		
		

};	
#endif