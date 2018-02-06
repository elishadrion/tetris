#include <time.h>
#include <unistd.h>
#include <iostream>
class Tetriminos{

	private:

		Block * _list_block;

	public:

		Tetriminos( int template_tetriminos[4][2]){
			
			_list_block = new Block[4];
			
			for(int i =0; i<4;i++){

				_list_block[i].setCoordinates(template_tetriminos[i][0],
											  template_tetriminos[i][1]
											  );
			} 
		}


		~Tetriminos(){

			delete[] _list_block;

		}

		

		Block * getListBlock(){return _list_block;}

		bool isBlockOfTetriminos(int Y, int X){
			bool flag = false;

			for(int i=0; i<4; i++){

				if(_list_block[i].get_Y() == Y && _list_block[i].get_X()==X){
					flag =true;
				}
			}
			return flag;
		}
		
		int get_Y_block_of(int k){

			return _list_block[k].get_Y();
		}

		int get_X_block_of(int k){

			return _list_block[k].get_X();
		}

	


		void drop(){
			bool flag = false;
			for(int i=0; i<4;i++){

				_list_block[i].setCoordinates( _list_block[i].get_Y()+1,
											   _list_block[i].get_X()

											  );

			}


		}

		void move_right(){
			if(_list_block[3].get_X()+1 <10){

				for(int i=0; i<4;i++){

					_list_block[i].setCoordinates(_list_block[i].get_Y(),
					    						  _list_block[i].get_X()+1);
			}
		}


		}

		void move_left(){
			if(_list_block[0].get_X() -1 > -1){
				for(int i=0; i<4;i++){

					_list_block[i].setCoordinates(_list_block[i].get_Y(),
												  _list_block[i].get_X()-1);
				}
			}


		}

		
	



};