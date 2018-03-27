/*
Groupe 2 : 3V-CUBE

Tetriminos.cpp
*/

#include "Tetriminos.hpp"
extern Random * g_rand_bonus ;
Tetriminos::Tetriminos(int color){
	/*
	Un tetriminos est un ensemble de 4 blocks.
	On crée une liste de block selon un des sept modèle
	de tetriminos généré aléatoirement.
		:param template_tetriminos: int[][]
	*/

	_list_block = new Block[4];

	int nbr_bonus = g_rand_bonus->nextInt(200)+1;
	int has_bonus = g_rand_bonus->nextInt(4)+1;

	for(int i =0; i<4;i++){


		_list_block[i].set_coordinates(TEMPLATE_TETRIMINOS[color][i][0],
									   TEMPLATE_TETRIMINOS[color][i][1]
									  );

		_list_block[i].set_color(color+1);
		_list_block[i].set_empty_state(false);

		if( nbr_bonus < 5 and has_bonus-1 == i){

			_list_block[i].set_bonus(has_bonus);
		}
		
	} 
}


Tetriminos::~Tetriminos(){

	delete[] _list_block;

}

int Tetriminos::get_coord_Y_of_block(int block)const{
	/*
	Cette fonction donne la coordonnée en Y du "Kième" block 
	de la liste de block du tetriminos.
		:param block: int
	*/
	return _list_block[block].get_Y();
}

int Tetriminos::get_coord_X_of_block(int block)const{
	/*
	Cette fonction donne la coordonnée en X du "Kième" block 
	de la liste de block du tetriminos.
		:param block: int
	*/

	return _list_block[block].get_X();
}

int Tetriminos::get_color_of_block(int block)const{

	return _list_block[block].get_color();
}


void Tetriminos::set_coord_of_block(int block, int y, int x){ 
	/*
	Cette fonction donne permet de changer les coordonnées
	d'un block d'un tétriminos.
		:param block: int
		:param y: int
		:param x: int
	*/
	_list_block[block].set_coordinates(y,x);
}


bool Tetriminos::has_block(int Y, int X)const{
	/*
	On vérifie si le tétriminos a un block de coordonnée 
	fournie en paramètre.
		:param Y: int
		:param X: int
		:return hasBlock: bool
	*/

	bool hasBlock = false;

	for(int i=0; i<4; i++){

		if(_list_block[i].get_Y() == Y and _list_block[i].get_X()==X){
			hasBlock =true;
		}
	}
	return hasBlock;
}


void Tetriminos::drop(){

	/*
	Cette fonction fait descendre d'une unité les blocks d'un tétriminos. 
	*/
	
	for(int i=0; i<4;i++){		

		_list_block[i].set_coordinates( _list_block[i].get_Y()+1,
									    _list_block[i].get_X()   );
			
	}
}

void Tetriminos::move_right(){
	/*
	Cette fonction permet de déplacer d'une unité
	vers la droite, les blocks d'un tétriminos.
	*/
	int blockMostRight = 0;

	// On regarde quel est le block du tétriminos qui est le plus à droite.

	for(int i=1; i<4; i++ ){
		if(_list_block[i].get_X() > _list_block[blockMostRight].get_X()){

			blockMostRight = i;
		}

	}

	// Et on déplace tout vers la droite.
	if(_list_block[blockMostRight].get_X()+1 <10){

		for(int i=0; i<4;i++){

			_list_block[i].set_coordinates(_list_block[i].get_Y(),
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

	// On regarde quel est le block du tétriminos qui est le plus à gauche.

	for(int i=1; i<4; i++ ){
		if(_list_block[i].get_X() < _list_block[blockMostLeft].get_X()){

			blockMostLeft = i;
		}

	}

	// Et on déplace tout vers la gauche.

	if(_list_block[blockMostLeft].get_X() -1 > -1){
		
		for(int i=0; i<4;i++){

			_list_block[i].set_coordinates(_list_block[i].get_Y(),
										  _list_block[i].get_X()-1);
		}
	}


}

void Tetriminos::turn( int rotationMat[2][2]){
	/*
	Cette fonction permet faire tourner dans le sens horlogé et
	anti-horlogé le tétrimino. 
		:param rotationMat: int[2][2]
	*/
	
	int matVector [2];
	int matTemp[2];
	int save;

	for(int i =0; i<4;i++){

		// Le deuxième block de chaque tétriminos est le pivot.
		if(i!=1){

			matVector[0] = _list_block[i].get_Y() - _list_block[1].get_Y();
			matVector[1] = _list_block[i].get_X() - _list_block[1].get_X();

			save = matVector[0];

			matVector[0] =( matVector[0] * rotationMat[0][0] )+(  matVector[1] * rotationMat[0][1]);
			matVector[1] =( save *  rotationMat[1][0] ) + (matVector[1] * rotationMat[1][1] );

			
			matTemp[0] = _list_block[1].get_Y() + matVector[0];
			matTemp[1] = _list_block[1].get_X() + matVector[1];
			_list_block[i].set_coordinates(matTemp[0],matTemp[1]);
			

		}

	}

}