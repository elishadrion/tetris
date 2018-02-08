/*
Groupe 2 : 3V-CUBE

Tetriminos.hpp
*/


#ifndef __TETRIMINOS__HPP__
#define __TETRIMINOS__HPP__
#include <time.h>
#include <unistd.h>

#include "Block.hpp"
class Tetriminos{

	private:

		Block * _list_block;

	public:

		Tetriminos( int template_tetriminos[4][2]);
		~Tetriminos();

		Block * getListBlock();
		int getCoordX_block(int k);
		int getCoordY_block(int k);

		bool hasBlock(int Y, int X);	

		void drop();
		void move_right();
		void move_left();

		void turn(int rotationMat[2][2]);
		



};
#endif