/*
Groupe 2 : 3V-CUBE

Block.cpp
*/

#include "Block.hpp"


Block::Block(){
	
	_coordinates = new int[2];

}
Block::~Block(){

	delete _coordinates;

}

int Block::get_color(){return _color;}

int Block::get_Y(){
	return _coordinates[0];
	
}

int Block::get_X(){
	return _coordinates[1];
	
}

void Block::set_color(int color){_color = color;}


void Block::set_coordinates(int Y, int X ){

	_coordinates[0]= Y;
	_coordinates[1]= X;
}


void Block::set_state(bool etat){
	_block_Empty = etat;
}


bool Block::is_empty() {

	return _block_Empty;
}