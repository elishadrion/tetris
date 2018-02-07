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

int Block::getColor(){return _color;}

int Block::get_Y(){
	return _coordinates[0];
	
}

int Block::get_X(){
	return _coordinates[1];
	
}

void Block::setColor(int color){_color = color;}


void Block::setCoordinates(int Y, int X ){

	_coordinates[0]= Y;
	_coordinates[1]= X;
}


void Block::setState(bool etat){
	_block_Empty = etat;
}


bool Block::isEmpty(){

	return _block_Empty;
}