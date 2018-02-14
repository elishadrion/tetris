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

		//Getter
		int get_color() ;
		int get_Y() ;
		int get_X() ;

		//Setter
		void set_color(int color);		
		void set_coordinates(int Y, int X );
		void set_state(bool etat);

		bool is_empty();
		
};
#endif