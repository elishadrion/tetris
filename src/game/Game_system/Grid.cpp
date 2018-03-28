/*
Groupe 2 : 3V-CUBE

Grid.cpp
*/

#include "Grid.hpp"


std::mutex mtx;
Random * g_rand_bonus ;



Grid::Grid(long seed) :  _grid(nullptr),_current_tetriminos(nullptr), _next_tetriminos(nullptr),
				_hold_tetriminos(nullptr),_ghost_tetriminos(nullptr),_number_generator( new Random(seed)),
				_destroy_block_generator(new Random(seed)),_acceleration(300000),
				_score(0), _level(0),_line_complete(0),_line_stack(0),_bonus(0),_stack_blank(false), _controller_inverse(false),
				_use_bonus(false){
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

	g_rand_bonus =  new Random(seed);
}

Grid::~Grid(){ 

	for(int i = 0; i<20; i++){

		delete[] _grid[i];								
	}
	delete[] _grid;

	if(_hold_tetriminos){delete _hold_tetriminos;}
	delete _current_tetriminos;
	delete _number_generator;

}



Tetriminos * Grid::get_tetriminos()const{

	return _current_tetriminos;
}

bool Grid::has_tetriminos_hold()const{

	return _hold_tetriminos;
}

Tetriminos * Grid::get_ghost_tetriminos()const{

	return _ghost_tetriminos;
}

Tetriminos * Grid::get_next_tetriminos()const{	
	
	return _next_tetriminos;
}

Tetriminos * Grid::get_hold_tetriminos()const{	
	
	return _hold_tetriminos;
}

int Grid::get_color_of_tetriminos()const{

	return _current_tetriminos->get_color_of_block(0);
}
int Grid::get_bonus()const{

	return _bonus;
}
int Grid::get_color_of_block(int i , int j)const{

	return _grid[i][j].get_color();
}

Block** Grid::get_grid()const{
	
	return _grid;
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
void Grid::set_grid(Block** grid){

	_grid = grid;
}

void Grid::set_state_stack_blank(bool state){
	_stack_blank = state;

}

void Grid::set_state_controller_inverse(bool state){

	_controller_inverse = state;
}

int Grid::get_score()const{return _score;}
int Grid::get_level()const{return _level;}
int Grid::get_line_complete()const {return _line_complete;}

bool Grid::is_empty(int i, int j)const{

	/*
	On vérifie si un block de la grille est vide ou 
	s'il est utilisé par un élément d'un Tétriminos.
		:param i: int
		:param j: int
		:return : bool
	*/

	return _grid[i][j].is_empty();

}

bool Grid::is_reaching_floor()const{
	/*
	On vérifie si le tétrimino peut encore faire un mouvement 
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


bool Grid::is_colliding_right()const {
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

bool Grid::is_stack_blank()const{

	return _stack_blank;
}

bool Grid::is_controller_inverse()const{

	return _controller_inverse;
}

bool Grid::is_colliding_left() const{
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

bool Grid::is_colliding_rotation(int rotationMat[2][2]) const{
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

bool Grid::is_overload()const{
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
			_grid[y][x].set_empty_state(0);

			// On met la couleur de ces blocks aux couleurs du tétriminos.
			_grid[y][x].set_color(_current_tetriminos->get_color_of_block(i));

			_grid[y][x].set_bonus(_current_tetriminos->get_bonus_of_block(i));
		}

	}

}

void Grid::ghost(){
	/*
	Le tetriminos courant va se casser et tous ses blocks vont remplacer
	les blocks vides de la grille.
	*/
	int k= 0;
	if(_ghost_tetriminos != nullptr){delete _ghost_tetriminos;}
	while(true){
		for(int i = 0; i<4; i++){

			int y = _current_tetriminos->get_coord_Y_of_block(i);
			int x = _current_tetriminos->get_coord_X_of_block(i);
			
			if(y+k+1 == 20 or is_empty(y+k+1,x) == false){
				
				_ghost_tetriminos  = new Tetriminos(2);
				_ghost_tetriminos->set_coord_of_block(0,_current_tetriminos->get_coord_Y_of_block(0)+k,
													   _current_tetriminos->get_coord_X_of_block(0) );
				_ghost_tetriminos->set_coord_of_block(1,_current_tetriminos->get_coord_Y_of_block(1)+k,
													   _current_tetriminos->get_coord_X_of_block(1) );
				_ghost_tetriminos->set_coord_of_block(2,_current_tetriminos->get_coord_Y_of_block(2)+k,
													   _current_tetriminos->get_coord_X_of_block(2) );
				_ghost_tetriminos->set_coord_of_block(3,_current_tetriminos->get_coord_Y_of_block(3)+k,
													   _current_tetriminos->get_coord_X_of_block(3) );
				return;
			}

			

		}

		k++;

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

				_grid[i][j].set_empty_state(true);
				_grid[i][j].set_color(0);
				

			
				
			}

			if(_line_stack-1 == i){ _line_stack-=1;}


		}


	line_complete = true;

	}
	// On va faire descendre chaque block après qu'une ligne soit supprimé.
	// On va faire la même opération pour le nombre de ligne complète.

	int color;
	for(int k =0 ; k < line_counter; k++){

		_score += 50 * pow(2,line_counter) * (_level+1);

		

		// On vérifie par le bas de la grille
		for(int i = 19; i> 0; i--){

			for(int j = 0; j<10; j++){
				
				if( (20-i) >= _line_stack and not(_grid[i-1][j].is_empty() ) and _grid[i][j].is_empty()){
					
					_grid[i-1][j].set_empty_state(true);
					_grid[i][j].set_empty_state(false);
					color = _grid[i-1][j].get_color();
					_grid[i][j].set_color(color);
					_grid[i-1][j].set_color(0);

					if(_bonus ==0 and  _grid[i][j].get_bonus()  != 0 and _grid[i][j].get_bonus() < 5){

						_bonus = _grid[i][j].get_bonus();
					}
				}					
					
			}			
		}

	}	
		_line_complete += line_counter;
		
		return line_counter;

}

void Grid::swap_grid(Grid* other_grid){

	Block ** save = get_grid();
	set_grid(other_grid->get_grid());
	other_grid->set_grid(save);

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
	Cette fonction permet déplacer à droite le tétriminos.
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

void Grid::use_bonus(){

	if(_bonus !=0){
		_use_bonus = true;
	}
}

void Grid::set_current_tetriminos_hold(){
	/*
	Cette fonction permet de conserver le tétriminos courant.
	*/

	if(not(_hold_tetriminos )){

		_hold_tetriminos = _current_tetriminos;
		_current_tetriminos = _next_tetriminos;
		_next_tetriminos = new Tetriminos(_number_generator->nextInt(7));

		int color ;
		color = _hold_tetriminos->get_color_of_block(0)-1;
		delete _hold_tetriminos;
		_hold_tetriminos = new Tetriminos(color);

	}
	else{


		delete _current_tetriminos;
		_current_tetriminos = _hold_tetriminos;
		_hold_tetriminos = nullptr;

		int color ;
		color = _current_tetriminos->get_color_of_block(0)-1;
		delete(_current_tetriminos);
		_current_tetriminos = new Tetriminos(color);
		

	}

}


int Grid::get_acceleration()const{ return _acceleration;}
void Grid::set_acceleration(int acceleration) { _acceleration = acceleration;}
void Grid::set_acceleration_quick(){set_acceleration(87654);}

void Grid::tetriminos_generator(){
	/*	
	Cette fonction permet de générer le tétriminos courant
	et le prochain tétriminos.
	*/

	int color = _number_generator->nextInt(7);
	
	if(not(_next_tetriminos)){
		_current_tetriminos = new Tetriminos(color);
	}
	else{
		delete _current_tetriminos;
		_current_tetriminos = _next_tetriminos;
	}

	color = _number_generator->nextInt(7);

	_next_tetriminos = new Tetriminos(color);
	
	
}


void Grid::update_score_level(){
	/*
	Monte le level du joueur si il a dépassé un score donnée.
	*/

	if(_score >= 2 * (_level+1) * 200 + _level*1000 ){_level +=1; }

}


void Grid::add_line(int line){

	/*
	On va ajouter des lignes à la grille du joueur, chaque ligne
	n'a que 9 cases pour que le joueur puisse les cassées.
	*/


	// On va d'abord monter tous les blocks de la grille.
	for(int i =0;i<20;i++){

		for(int j =0; j<10; j++ ){

			if( i-line >=0  ){

				_grid[i-line][j].set_empty_state(_grid[i][j].get_state());
				_grid[i-line][j].set_color(_grid[i][j].get_color());
				_grid[i][j].set_color(0);


			}

		}

	}	


	// On ajoute ainsi des blocks de couleurs aléatoire, 
	// pour chaque ligne, il y aura un block vide.
	for(int i =line;i>0;i--){

		int random_block = rand()%10;

		for(int j =0; j<10; j++ ){			

				if(j!= random_block ){

					_grid[20-i][j].set_empty_state(false);
					_grid[20-i][j].set_color(_number_generator->nextInt(7) +1);
				}

				else{
					_grid[20-i][j].set_empty_state(true);
					_grid[20-i][j].set_color(0);
				}

  		}

	}


	_line_stack +=line;

}

void Grid::destroy_block(){


	for(int i = 0; i<20; i++){

		for(int j = 0; j<10; j++){
			int x = (_destroy_block_generator->nextInt(100)) +1;
			if(is_empty(i,j) == false){

				if(x<5){

					_grid[i][j].set_empty_state(true);
					_grid[20-i][j].set_color(0);
				}
			}

		}
	}	




}


void Grid::hide_stack(Grid * other_grid){

	other_grid->set_state_stack_blank(true);
	sleep(5);
	other_grid->set_state_stack_blank(false);
	

}

void Grid::inverse_controller(Grid * other_grid){

	set_state_controller_inverse(true);
	sleep(5);
	set_state_controller_inverse(false);

}


void Grid::active_bonus(Grid * other_grid){

	if(_use_bonus ==true and _bonus!= 0){

		if(_bonus == 1){

			swap_grid(other_grid);
		}
		else if(_bonus ==2){

			hide_stack(other_grid);

		}

		else if(_bonus ==3){

			inverse_controller(other_grid);
		}
		else if(_bonus==4){

			destroy_block();

		}

		_use_bonus = false; 
		_bonus = 0;

	}

}