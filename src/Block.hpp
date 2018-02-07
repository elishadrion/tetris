/*
Groupe 2 : 3V-CUBE

Block.hpp
*/
#ifndef __Block__HPP__
#define __Block__HPP__

class Block {


	private:

		int _color = 0;
		int * _coordinates;
		bool _block_Empty = true;


	public:

		Block();
		~Block();

		int getColor();
		int get_Y();
		int get_X();

		void setColor(int color);		
		void setCoordinates(int Y, int X );
		void setState(bool etat);

		bool isEmpty();
		







};
#endif