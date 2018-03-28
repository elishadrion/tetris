/*
Groupe 2 : 3V-CUBE

Block.cpp
*/

#include "Block.hpp"

Block::Block(): _color(0), _coordinates(new int[2]), _empty_block(1), _bonus(0) {}

Block::~Block(){

	delete _coordinates;

}

int Block::get_color()const{return _color;}

int Block::get_Y()const{	return _coordinates[0];}

int Block::get_X()const{ return _coordinates[1];}
int Block::get_bonus() const{return _bonus;}
void Block::set_color(int color){_color = color;}

void Block::set_coordinates(int Y, int X ){

	_coordinates[0]= Y;
	_coordinates[1]= X;
}

void Block::set_empty_state(bool etat){
	_empty_block = etat;
}


bool Block::is_empty() const{

	return _empty_block == true;
}

bool Block::get_state()const{

	return _empty_block;
}

void Block::set_bonus(int bonus){ _bonus = bonus;}