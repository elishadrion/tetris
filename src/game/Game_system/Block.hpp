/*
Groupe 2 : 3V-CUBE

Block.hpp
*/
#ifndef __Block__HPP__
#define __Block__HPP__


class Block {


	private:

		int _color;
		int * _coordinates;
		bool _empty_block;
		int _bonus;
		

	public:

		Block();
		~Block();

		//Getter
		int get_color()const;
		bool get_state()const;
		int get_Y() const ;
		int get_X() const;
		int get_bonus() const;
		

		//Setter
		void set_color(int color);		
		void set_coordinates(int Y, int X );
		void set_empty_state(bool etat);
		void set_bonus(int bonus);


		bool is_empty() const;
		
};
#endif