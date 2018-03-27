/*
Groupe 2 : 3V-CUBE

Tetriminos.hpp
*/


#ifndef __TETRIMINOS__HPP__
#define __TETRIMINOS__HPP__

#include <time.h>
#include <unistd.h>
#include "Block.hpp"
#include "../../common/Random.hpp"

const int TEMPLATE_TETRIMINOS[7][4][2] = {
											 {{0,4}, {0,5}, {-1,4},{-1,5}},  // carré
											 {{0,3}, {0,4}, {0,5}, {0,6}},	 // barre
											 {{0,3}, {-1,3},{0,4}, {0,5}},   // L gauche
											 {{0,4}, {0,5}, {0,6}, {-1,6}},  // L droit
											 {{0,3}, {0,4}, {-1,4},{-1,5}},  // Z gauche
											 {{-1,4},{-1,5},{0,5}, {0,6}},   // Z droit
											 {{0,3}, {0,4}, {-1,4},{0,5}}    // T 
										 };




class Tetriminos{

	private:

		Block * _list_block;		

	public:

		Tetriminos( int color);
		~Tetriminos();

		//Getter
		
		int get_coord_X_of_block(int block)const;
		int get_coord_Y_of_block(int block )const;
		int get_color_of_block(int block)const;

		//Setter
		void set_coord_of_block(int block, int y, int x);

		// Move
		void drop();
		void move_left();
		void move_right();
		void turn(int rotationMat[2][2]);

		bool has_block(int Y, int X)const;	
		
};
#endif