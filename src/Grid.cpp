/*
Groupe 2 : 3V-CUBE

Grid.cpp
*/

#include "Grid.hpp"
#include <mutex>

std::mutex mtx; 


Grid::Grid() : _grid(nullptr),_currentTetriminos(nullptr), _hold_Tetriminos(nullptr), hold(false){
	/*
	On construit une grille de 20 x 10.
	Une grille d'objet de type "Block" vide.
	*/

	_grid = new Block*[20];

	for(int i = 0; i<20; i++){

		_grid[i] = new Block[10];

		for(int j = 0; j<10; j++){

			_grid[i][j].set_coordinates(i,j);

		}
	}
	
}

Grid::~Grid(){ 

	for(int i = 0; i<20; i++){

		delete[] _grid[i];								
	}
	delete[] _grid;
}


Block Grid::get_block(int i, int j){

	return _grid[i][j];
}

Tetriminos * Grid::get_tetriminos(){

	return _currentTetriminos;
}

bool Grid::has_tetriminos_hold(){

	return hold;
}

void Grid::set_state_tetriminos_hold(bool state){ hold = state;}


Tetriminos * Grid::get_hold_tetriminos(){	
	
	return _hold_Tetriminos;
}

int Grid::get_color_of_tetriminos(){

	return _currentTetriminos->get_color_of_block(0);
}

int Grid::get_color_of_block(int i , int k){

	return _grid[i][k].get_color();
}

void Grid::set_tetriminos(Tetriminos * tetriminos){    

	_currentTetriminos = tetriminos;
}

void Grid::set_hold_tetriminos(Tetriminos * tetriminos){    

	_hold_Tetriminos = tetriminos;
}


bool Grid::is_empty(int i, int j){

	/*
	On vérifie si un block de la grille est vide ou 
	s'il est utilisé par un élément d'un Tétriminos.
		:param i: int
		:param j: int
		:return : bool
	*/

	return _grid[i][j].is_empty();

}

bool Grid::is_reaching_floor(){
	/*
	On vérifie si le Tétriminos peut encore faire un mouvement 
	vers le bas.
		:return can_drop: bool
	*/

	bool can_drop = false;

	for(int i =0; i<4; i++){
		
		if( _currentTetriminos->get_coord_Y_of_block(i) == 19 
		    or _grid[_currentTetriminos->get_coord_Y_of_block(i)+1]
			        [_currentTetriminos->get_coord_X_of_block(i)].is_empty() == false ) 

			{can_drop = true;}


	}
	return can_drop;

}


bool Grid::is_colliding_right() {
	/*
	Vérifie si un tétriminos peut faire un mouvement faire la droite.
		:return cantMove: bool
	*/
	bool cantMove = false;

	for(int i =0; i<4; i++){
		
		if(  _currentTetriminos->get_coord_Y_of_block(i)<0 or
			_grid[_currentTetriminos->get_coord_Y_of_block(i)]
			      [_currentTetriminos->get_coord_X_of_block(i)+1].is_empty() == false ) 

			{cantMove = true;}

	}
	return cantMove;
	
}

bool Grid::is_colliding_left() {
	/*
	Vérifie si un tétriminos peut faire un mouvement faire la gauche.
		:param cantMove: bool
	*/

	bool cantMove = false;

	for(int i =0; i<4; i++){
		
		if(  _currentTetriminos->get_coord_Y_of_block(i)<0 or
			_grid[_currentTetriminos->get_coord_Y_of_block(i)]
			     [_currentTetriminos->get_coord_X_of_block(i)-1].is_empty() == false ) 

			{cantMove = true;}

	}
	return cantMove;
	
}

bool Grid::is_colliding_rotation(int rotationMat[2][2]) {
	/*
	Vérifie si un tétriminos peut faire une rotation vers la droite ou la gauche.
		:param cantTurn: bool
	*/
	bool cantTurn = false;
	int matVector [2];

	for(int i =0; i<4 ;i++){

		// Le deuxième block de chaque tétriminos est le pivot.
		if(i!=1){

			matVector[0] = _currentTetriminos->get_coord_Y_of_block(i) -  _currentTetriminos->get_coord_Y_of_block(1);
			matVector[1] = _currentTetriminos->get_coord_X_of_block(i) -  _currentTetriminos->get_coord_X_of_block(1);

		
			int save = matVector[0];

			matVector[0] =( matVector[0] * rotationMat[0][0] )+(  matVector[1] * rotationMat[0][1]);
			matVector[1] =( save *  rotationMat[1][0] ) + (matVector[1] * rotationMat[1][1] );

			int matTemp[2];
			matTemp[0] = _currentTetriminos->get_coord_Y_of_block(1) + matVector[0];
			matTemp[1] = _currentTetriminos->get_coord_X_of_block(1) + matVector[1];
				
			if( matTemp[0]<0 or matTemp[1]<0 or matTemp[1]>10 or 
			    _grid[matTemp[0]][matTemp[1]].is_empty() == false ){

			    cantTurn = true;
			}

		}

	}

	return cantTurn;
}

bool Grid::is_overload(){
	/*
	Cette fonction vérifie si la grille n'est pas surcharger.
		return isOverload: bool
	*/

	bool isOverload = false;
	for(int i =0; i<4; i++){
		
		if(_currentTetriminos->get_coord_Y_of_block(i) == 0 and
		   _currentTetriminos->get_coord_X_of_block(i) > 2 and
		   _currentTetriminos->get_coord_X_of_block(i) < 6   ){


			isOverload = true;
		}

	}

	return isOverload;
}

void Grid::fix_block(){
	/*
	Le tetriminos courant va se casser et tous ses blocks vont remplacer
	les blocks vides de la grille.
	*/
	
	for(int i =0; i<4; i++){
		
		// On met l'état des blocks de la grille à non vide.
		_grid[_currentTetriminos->get_coord_Y_of_block(i)]
			 [_currentTetriminos->get_coord_X_of_block(i)].set_state(false);

		// On met la couleur de ces blocks aux couleurs du tétriminos.
		_grid[_currentTetriminos->get_coord_Y_of_block(i)]
			 [_currentTetriminos->get_coord_X_of_block(i)].set_color(_currentTetriminos->get_color_of_block(i));

	}

}


int Grid::check_lines(){
	/*	
	On vérifie chaque ligne de la grille et on les supprime
	si elles sont complètes. On réarrange ainsi la grille.
	*/

	int line_counter = 0;   
	bool line_complete = true; // On part du principe qu'une ligne est complète.

	/*
	On parcourt la grille pour trouver les lignes complètes.
	*/

	for(int i = 0; i< 20; i++){

		for(int j = 0; j<10; j++){

			// si un block est vide alors la ligne ne peut etre complète.
			if( _grid[i][j].is_empty() ){ line_complete = false;}
		}

		/*
		Si on a une ligne complète, on attribut l'état de chaque block 
		à vide et on incrémente le compteur de ligne.
		*/

		if(line_complete == true){
			line_counter +=1;

			for(int j = 0; j<10; j++){

				_grid[i][j].set_state(true);
			}

		}


	line_complete = true;

	}
	// On va faire descendre chaque block après qu'une ligne soit supprimé.
	// On va faire la même opération pour le nombre de ligne complète.
	for(int k =0; k < line_counter; k++){

		// On vérifie par le bas de la grille
		for(int i = 19; i> 0; i--){

			for(int j = 0; j<10; j++){
				
				if( not(_grid[i-1][j].is_empty() ) and _grid[i][j].is_empty()){
					

					_grid[i][j].set_state(false);
					_grid[i-1][j].set_state(true);}}
				}


		}

		return line_counter;

}

bool Grid::tetriminos_try_drop(){
	/*
	Cette fonction permet de faire descendre le tétriminos, il vérifie 
	qu'il ne frole pas le sol.
		:return flag: bool
	*/

	bool can_drop = true;
	mtx.lock();

	if( not(is_reaching_floor())){
		_currentTetriminos->drop();
	}	
	else{
		can_drop = false;
	}

	mtx.unlock();

	return can_drop;
}

void Grid::current_tetriminos_move_right(){
	/*
	Cette focntion permet déplacer à droite le tétriminos.
	*/
	if(not(is_colliding_right())){ _currentTetriminos->move_right(); }

}


void Grid::current_tetriminos_move_left(){
	/*
	Cette focntion permet déplacer à gauche le tétriminos.
	*/
	if(not(is_colliding_left())){_currentTetriminos->move_left();}


}


void Grid::current_tetriminos_hard_drop(){
	/*
	Cette focntion permet de faire descendre le tétriminos
	jusqu'à qu'il frole le sol.
	*/
	while( tetriminos_try_drop()){}
	
}

void Grid::current_tetriminos_turn_left(){
	/*
	Cette fonction permet de tourner le tétriminos vers la gauche.
	*/

	int matRotation[2][2] =  {{0,-1},{1,0}};

	if( not(is_colliding_rotation(matRotation)) )
		{_currentTetriminos->turn(matRotation);}


}

void Grid::current_tetriminos_turn_right(){
	/*
	Cette fonction permet de tourner le tétriminos vers la droite.
	*/

	int matRotation[2][2] =  {{0,1},{-1,0}};

	if( not(is_colliding_rotation(matRotation)) )
		{_currentTetriminos->turn(matRotation);};


}

void Grid::set_current_tetriminos_hold(){
	/*
	Cette fonction permet de conserver le tétriminos courant.
	*/

	if(hold == false){

		Tetriminos * save =_hold_Tetriminos;
		 _hold_Tetriminos = _currentTetriminos;
		 _currentTetriminos = save;

		 int x ;

		 for(int i=0; i<4; i++){
		 	x = _hold_Tetriminos->get_color_of_block(0) -1;

		 	_hold_Tetriminos->set_coord_of_block(i, TEMPLATE_TETRIMINOS[x][i][0], 											
		 	                                        TEMPLATE_TETRIMINOS[x][i][1]);

		 	x = _currentTetriminos->get_color_of_block(0)-1;

		 	_currentTetriminos->set_coord_of_block(i, TEMPLATE_TETRIMINOS[x][i][0],
		 										      TEMPLATE_TETRIMINOS[x][i][1]);

		 }

		 hold =true;
	}

}
