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

	public:

		Grid();
		~Grid();

		//Getter
		Block getBlock(int i, int j);
		Tetriminos * getTetriminos();

		//Setter
		void setTetriminos(Tetriminos * tetriminos);

		bool isReachingFloor();
		bool isCollidingRight();
		bool isCollidingLeft();
		bool isEmpty(int i, int j);

		void fix_block();
		void check_lines();

		void currentTetriminosMoveRight();
		void currentTetriminosMoveLeft();
		



};
#endif