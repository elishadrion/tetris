/*
Groupe 2 : 3V-CUBE

Tetriminos.cpp
*/

#include "Tetriminos.hpp"


Tetriminos::Tetriminos( int template_tetriminos[4][2]){
	/*
	:param template_tetriminos: int[][]

		Un tetriminos est un ensemble de 4 blocks.
		On crée une liste de block selon un des sept modèle
		de tetriminos généré aléatoirement.
	*/
	_list_block = new Block[4];
	
	for(int i =0; i<4;i++){

		_list_block[i].setCoordinates(template_tetriminos[i][0],
									  template_tetriminos[i][1]
									  );
	} 
}


Tetriminos::~Tetriminos(){

	delete[] _list_block;

}



Block * Tetriminos::getListBlock(){return _list_block;}


int Tetriminos::getCoordY_block(int k){
	/*
	:param k: int

		Cette fonction donne la coordonnée en Y du "Kième" block 
		de la liste de block du tetriminos.
		*/
	return _list_block[k].get_Y();
}

int Tetriminos::getCoordX_block(int k){
	/*
	:param k: int

		Cette fonction donne la coordonnée en X du "Kième" block 
		de la liste de block du tetriminos.
		*/

	return _list_block[k].get_X();
}


bool Tetriminos::hasBlock(int Y, int X){
	/*
	:param Y: int
	:param X: int
	:return flag: bool

		On vérifie si le tétriminos a un block de coordonnée 
		fournie en paramètre.
	*/

	bool flag = false;

	for(int i=0; i<4; i++){

		if(_list_block[i].get_Y() == Y and _list_block[i].get_X()==X){
			flag =true;
		}
	}
	return flag;
}






void Tetriminos::drop(){

	/*
	Cette fonction fait descendre d'une unité les blocks d'un tétriminos. 

	*/
	
	for(int i=0; i<4;i++){

		_list_block[i].setCoordinates( _list_block[i].get_Y()+1,
									   _list_block[i].get_X()   );

	}


}

void Tetriminos::move_right(){
	/*
	Cette fonction permet de déplacer d'une unité
	vers la droite, les blocks d'un tétriminos.
	*/
	int blockMostRight = 0;

	for(int i=1; i<4; i++ ){
		if(_list_block[i].get_X() > _list_block[blockMostRight].get_X()){

			blockMostRight = i;
		}

	}

	if(_list_block[blockMostRight].get_X()+1 <10){

		for(int i=0; i<4;i++){

			_list_block[i].setCoordinates(_list_block[i].get_Y(),
			    						  _list_block[i].get_X()+1);
	}
}


}

void Tetriminos::move_left(){
	/*
	Cette fonction permet de déplacer d'une unité
	vers la gauche, les blocks d'un tétriminos.
	*/

	int blockMostLeft = 0;

	for(int i=1; i<4; i++ ){
		if(_list_block[i].get_X() < _list_block[blockMostLeft].get_X()){

			blockMostLeft = i;
		}

	}

	if(_list_block[blockMostLeft].get_X() -1 > -1){
		
		for(int i=0; i<4;i++){

			_list_block[i].setCoordinates(_list_block[i].get_Y(),
										  _list_block[i].get_X()-1);
		}
	}


}

void Tetriminos::turn( int rotationMat[2][2]){
	/*
	:param rotationMat: int[2][2]
	
		Cette fonction permet faire tourner dans le sens horlogé et
		anti-horlogé le tétrimino. 

	*/
	
	int matVector [2];
	for(int i =0; i<4;i++){

		// Le deuxième block de chaque tétriminos est le pivot.
		if(i!=1){

			matVector[0] = _list_block[i].get_Y() - _list_block[1].get_Y();
			matVector[1] = _list_block[i].get_X() - _list_block[1].get_X();

		

			int save = matVector[0];

			matVector[0] =( matVector[0] * rotationMat[0][0] )+(  matVector[1] * rotationMat[0][1]);
			matVector[1] =( save *  rotationMat[1][0] ) + (matVector[1] * rotationMat[1][1] );

			int matTemp[2];
			matTemp[0] = _list_block[1].get_Y() + matVector[0];
			matTemp[1] = _list_block[1].get_X() + matVector[1];
			_list_block[i].setCoordinates(matTemp[0],matTemp[1]);
			_list_block[i].setState(false);

		}

	}

}

