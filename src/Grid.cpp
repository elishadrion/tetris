/*
Groupe 2 : 3V-CUBE

Grid.cpp
*/

#include "Grid.hpp"


Grid::Grid() : _grid(nullptr),_currentTetriminos(nullptr), _hold_Tetriminos(nullptr){
	/*
	On construit une grille de 20 x 10.
	Une grille d'objet de type "Block" vide.
	*/

	_grid = new Block*[20];

	for(int i = 0; i<20; i++){

		_grid[i] = new Block[10];

		for(int j = 0; j<10; j++){

			_grid[i][j].setCoordinates(i,j);

		}
	}

			

	
}

Grid::~Grid(){ 

	for(int i = 0; i<20; i++){
		delete[] _grid[i];								
	}

	delete[] _grid;
}



Block Grid::getBlock(int i, int j){ return _grid[i][j];}

Tetriminos * Grid::getTetriminos(){return _currentTetriminos;}



void Grid::setTetriminos(Tetriminos * tetriminos){    

	_currentTetriminos = tetriminos;
}


bool Grid::isEmpty(int i, int j){

	/*
	:param i: int
	:param j: int
	:return : bool
		On vérifie si un block de la grille est vide ou 
		s'il est utilisé par un élément d'un Tétriminos.	
	*/

	return _grid[i][j].isEmpty();

}

bool Grid::isReachingFloor(){
	/*
	:return : bool

		On vérifie si le Tétriminos peut encore faire un mouvement 
		vers le bas.
	*/
	bool flag = false;

	for(int i =0; i<4; i++){
		
		if( _currentTetriminos->getCoordY_block(i) == 19 
		    or _grid[_currentTetriminos->getCoordY_block(i)+1]
			        [_currentTetriminos->getCoordX_block(i)].isEmpty() == false ) 

			{flag = true;}


	}
	return flag;

}


bool Grid::isCollidingRight() {
	/*
	:return cantMove: bool
	Vérifie si un tétriminos peut faire un mouvement faire la droite.
	*/
	bool cantMove = false;

	for(int i =0; i<4; i++){
		
		if(  _grid[_currentTetriminos->getCoordY_block(i)]
			      [_currentTetriminos->getCoordX_block(i)+1].isEmpty() == false ) 

			{cantMove = true;}


	}
	return cantMove;

	
}

bool Grid::isCollidingLeft() {
	/*
	:param cantMove: bool
		Vérifie si un tétriminos peut faire un mouvement faire la gauche.
	*/

	bool cantMove = false;

	for(int i =0; i<4; i++){
		
		if( _grid[_currentTetriminos->getCoordY_block(i)]
			     [_currentTetriminos->getCoordX_block(i)-1].isEmpty() == false ) 

			{cantMove = true;}


	}
	return cantMove;

	
}


bool Grid::isCollidingRotation(int rotationMat[2][2]) {
	/*
	:param cantTurn: bool
		Vérifie si un tétriminos peut faire une rotation vers la droite ou la gauche.
	*/
	bool cantTurn = false;
	int matVector [2];

	for(int i =0; i<4 ;i++){

		// Le deuxième block de chaque tétriminos est le pivot.
		if(i!=1){

			matVector[0] = _currentTetriminos->getCoordY_block(i) -  _currentTetriminos->getCoordY_block(1);
			matVector[1] = _currentTetriminos->getCoordX_block(i) -  _currentTetriminos->getCoordX_block(1);

		

			int save = matVector[0];

			matVector[0] =( matVector[0] * rotationMat[0][0] )+(  matVector[1] * rotationMat[0][1]);
			matVector[1] =( save *  rotationMat[1][0] ) + (matVector[1] * rotationMat[1][1] );

			int matTemp[2];
			matTemp[0] = _currentTetriminos->getCoordY_block(1) + matVector[0];
			matTemp[1] = _currentTetriminos->getCoordX_block(1) + matVector[1];
				
			if( matTemp[0]<0 or matTemp[1]<0 or matTemp[1]>10 or 
			    _grid[matTemp[0]][matTemp[1]].isEmpty() == false )
			    { cantTurn = true;}

		}

	}

	return cantTurn;
}



bool Grid::fix_block(){
	/*
	Le tetriminos courant va se casser et tous ses blocks vont remplacer
	les blocks vides de la grille.
	*/
	bool flag = false;
	for(int i =0; i<4; i++){
		
		_grid[_currentTetriminos->getCoordY_block(i)]
			 [_currentTetriminos->getCoordX_block(i)].setState(false);
		
		if(_currentTetriminos->getCoordY_block(i) == 0 and
		   _currentTetriminos->getCoordX_block(i) > 2 and
		   _currentTetriminos->getCoordX_block(i) < 6   ){


			flag = true;
		}



	}

	return flag;
}


void Grid::check_lines(){
	/*	
	On vérifie chaque ligne de la grille et on les supprime
	si elles sont complètes. On réarrange ainsi la grille.
	*/

	int lineCounter = 0;   
	bool line_complete = true; // On part du principe qu'une ligne est complète.

	/*
	On parcourt la grille pour trouver les lignes complètes.
	*/

	for(int i = 0; i< 20; i++){

		for(int j = 0; j<10; j++){

			// si un block est vide alors la ligne ne peut etre complète.
			if( _grid[i][j].isEmpty() ){ line_complete = false;}
		}

		/*
		Si on a une ligne complète, on attribut l'état de chaque block 
		à vide et on incrémente le compteur de ligne.
		*/

		if(line_complete == true){
			lineCounter +=1;

			for(int j = 0; j<10; j++){

				_grid[i][j].setState(true);
			}

		}


	line_complete = true;

	}
	// On va faire descendre chaque block après qu'une ligne soit supprimé.
	// On va faire la même opération pour le nombre de ligne complète.
	for(int k =0; k < lineCounter; k++){

		// On vérifie par le bas de la grille
		for(int i = 19; i> 0; i--){

			for(int j = 0; j<10; j++){
				
				if( not(_grid[i-1][j].isEmpty() ) and _grid[i][j].isEmpty()){
					

					_grid[i][j].setState(false);
					_grid[i-1][j].setState(true);}}
				}


		}



}


void Grid::currentTetriminosMoveRight(){

	if(not(isCollidingRight())){_currentTetriminos->move_right();}


}


void Grid::currentTetriminosMoveLeft(){

	if(not(isCollidingLeft())){_currentTetriminos->move_left();}


}

void Grid::currentTetriminosTurnRight(){
	int matRotation[2][2] =  {{0,1},{-1,0}};
	if( not(isCollidingRotation(matRotation)) ){_currentTetriminos->turn(matRotation);};


}

void Grid::currentTetriminosTurnLeft(){
	int matRotation[2][2] =  {{0,-1},{1,0}};
	if( not(isCollidingRotation(matRotation)) ){_currentTetriminos->turn(matRotation);}


}