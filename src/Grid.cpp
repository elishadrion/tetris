/*
Groupe 2 : 3V-CUBE

Grid.cpp
*/

#include "Grid.hpp"
#include <mutex>
#include <fstream>
#include<iostream>


std::mutex mtx; 


Grid::Grid() : _grid(nullptr),_current_tetriminos(nullptr), _next_tetriminos(nullptr),
				_hold_tetriminos(nullptr),_acceleration(300000),quick_mode(false),
				_score(0), _level(0) {
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

	return _current_tetriminos;
}

bool Grid::has_tetriminos_hold(){

	return _hold_tetriminos;
}




Tetriminos * Grid::get_next_tetriminos(){	
	
	return _next_tetriminos;
}

Tetriminos * Grid::get_hold_tetriminos(){	
	
	return _hold_tetriminos;
}

int Grid::get_color_of_tetriminos(){

	return _current_tetriminos->get_color_of_block(0);
}

int Grid::get_color_of_block(int i , int k){

	return _grid[i][k].get_color();
}

void Grid::set_tetriminos(Tetriminos * tetriminos){    

	_current_tetriminos = tetriminos;
}

void Grid::set_next_tetriminos(Tetriminos * tetriminos){    

	_next_tetriminos = tetriminos;
}

void Grid::set_hold_tetriminos(Tetriminos * tetriminos){    

	_hold_tetriminos = tetriminos;
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
		

		if( _current_tetriminos->get_coord_Y_of_block(i) == 19 
		    or _grid[_current_tetriminos->get_coord_Y_of_block(i)+1]
			        [_current_tetriminos->get_coord_X_of_block(i)].is_empty() == false ) 

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
		
		if(  _current_tetriminos->get_coord_Y_of_block(i)<0 or
			_grid[_current_tetriminos->get_coord_Y_of_block(i)]
			      [_current_tetriminos->get_coord_X_of_block(i)+1].is_empty() == false ) 

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
		
		if(  _current_tetriminos->get_coord_Y_of_block(i)<0 or
			_grid[_current_tetriminos->get_coord_Y_of_block(i)]
			     [_current_tetriminos->get_coord_X_of_block(i)-1].is_empty() == false ) 

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

			int y_block = _current_tetriminos->get_coord_Y_of_block(i);
			int x_block = _current_tetriminos->get_coord_X_of_block(i); 

			int y_pivot = _current_tetriminos->get_coord_Y_of_block(1);
			int x_pivot = _current_tetriminos->get_coord_X_of_block(1); 

			matVector[0] = y_block -  y_pivot;
			matVector[1] = x_block -  x_pivot;
		
			int save = matVector[0];

			matVector[0] =( matVector[0] * rotationMat[0][0] )+(  matVector[1] * rotationMat[0][1]);
			matVector[1] =( save *  rotationMat[1][0] ) + (matVector[1] * rotationMat[1][1] );

			int matTemp[2];

			matTemp[0] = y_pivot + matVector[0];
			matTemp[1] = x_pivot + matVector[1];
				
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
		
		if(_current_tetriminos->get_coord_Y_of_block(i) == 0 and
		   _current_tetriminos->get_coord_X_of_block(i) > 2 and
		   _current_tetriminos->get_coord_X_of_block(i) < 6   ){


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

		int y = _current_tetriminos->get_coord_Y_of_block(i);
		int x = _current_tetriminos->get_coord_X_of_block(i);

		if( y>=0){

			// On met l'état des blocks de la grille à non vide.
			_grid[y][x].set_state(false);

			// On met la couleur de ces blocks aux couleurs du tétriminos.
			_grid[y][x].set_color(_current_tetriminos->get_color_of_block(i));
		}

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
				_grid[i][j].set_color(0);
				
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
					
					_grid[i-1][j].set_state(true);
					_grid[i][j].set_state(false);
					int color = _grid[i-1][j].get_color();
					_grid[i][j].set_color(color);
					_grid[i-1][j].set_color(0);
				}
					
					
			}
			
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
		_current_tetriminos->drop();
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
	if(not(is_colliding_right())){ _current_tetriminos->move_right(); }

}


void Grid::current_tetriminos_move_left(){
	/*
	Cette focntion permet déplacer à gauche le tétriminos.
	*/
	if(not(is_colliding_left())){_current_tetriminos->move_left();}

}

void Grid::current_tetriminos_hard_drop(){
	/*
	Cette focntion permet de faire descendre le tétriminos
	jusqu'à qu'il frole le sol.
	*/
	while( tetriminos_try_drop()){ _score +=2;}
	
}

void Grid::current_tetriminos_turn_left(){
	/*
	Cette fonction permet de tourner le tétriminos vers la gauche.
	*/

	int matRotation[2][2] =  {{0,-1},{1,0}};

	if( not(is_colliding_rotation(matRotation)) )
		{_current_tetriminos->turn(matRotation);}


}

void Grid::current_tetriminos_turn_right(){
	/*
	Cette fonction permet de tourner le tétriminos vers la droite.
	*/

	int matRotation[2][2] =  {{0,1},{-1,0}};

	if( not(is_colliding_rotation(matRotation)) )
		{_current_tetriminos->turn(matRotation);};


}

void Grid::set_current_tetriminos_hold(){
	/*
	Cette fonction permet de conserver le tétriminos courant.
	*/

	if(_hold_tetriminos == nullptr){

		_hold_tetriminos = _current_tetriminos;
		_current_tetriminos = _next_tetriminos;
		_next_tetriminos = new Tetriminos(rand()%7);

		int color ;

		for(int i=0; i<4; i++){
		 	
		 	color = _hold_tetriminos->get_color_of_block(0)-1;

		 	_hold_tetriminos->set_coord_of_block(i, TEMPLATE_TETRIMINOS[color][i][0],
		 										    TEMPLATE_TETRIMINOS[color][i][1]);
		 }
		

	}



	else if(_hold_tetriminos){

		delete _next_tetriminos;
		_next_tetriminos = _current_tetriminos;
		_current_tetriminos = _hold_tetriminos;
		_hold_tetriminos = nullptr;
		

		int color ;

		for(int i=0; i<4; i++){
		 	
		 	color = _current_tetriminos->get_color_of_block(0)-1;

		 	_current_tetriminos->set_coord_of_block(i, TEMPLATE_TETRIMINOS[color][i][0],
		 										       TEMPLATE_TETRIMINOS[color][i][1]);
		 	color = _next_tetriminos->get_color_of_block(0) -1;

		 	_next_tetriminos->set_coord_of_block(i, TEMPLATE_TETRIMINOS[color][i][0], 											
		 	                                        TEMPLATE_TETRIMINOS[color][i][1]);
		}

	}

}


int Grid::get_acceleration(){ return _acceleration;}
void Grid::set_acceleration(int acceleration) { _acceleration =acceleration;}
void Grid::set_acceleration_quick(){set_acceleration(87654);}


void Grid::tetriminos_generator(){
	/*	
	Cette fonction permet de générer le tétriminos courant
	et le prochain tétriminos.
	*/

	int color = rand()%7;
	
	if(_next_tetriminos == nullptr){
		_current_tetriminos = new Tetriminos(color);
	}
	else{

		_current_tetriminos = _next_tetriminos;
	}

	color = rand()%7;

	_next_tetriminos = new Tetriminos(color);
	
	
}



char * Grid::grid_to_char(){


	char info[202]="a";

	for(int i =0; i<20;i++){

		for(int j = 0; j<10;j++){

			info[10*i+j]= _grid[i][j].get_color() + 48;

		}

		for(int i =0; i<4;i++){

			int y = _current_tetriminos->get_coord_Y_of_block(i);
			int x = _current_tetriminos->get_coord_X_of_block(i); 
			info[10*y+x] = _current_tetriminos->get_color_of_block(i) + 48;
		}

		info[200]= _next_tetriminos->get_color_of_block(0) +48;
		if(_hold_tetriminos!=nullptr){ info[201]= _hold_tetriminos->get_color_of_block(0) +48;}
		else{info[201]= 48; }
		info[202]= '\0';


	}
		std::ofstream fichier ("test.txt");  // ouverture en écriture avec effacement du fichier ouvert
 
       
                
                fichier <<info;
 
                fichier.close();
       
 
 


	return info;
}


