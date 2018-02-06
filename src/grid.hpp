
#include <iostream>

class grid{

	private:
		Block ** grille;
		Tetriminos * current_Tetriminos;
		Tetriminos * hold_Tetriminos;

	public:

		grid(){

			grille = new Block*[20];

			for(int i = 0; i<20; i++){

				grille[i] = new Block[10];

				for(int j = 0; j<10; j++){

					grille[i][j].setCoordinates(i,j);

				}
			}

					

			
		}

		~grid(){ 
			for(int i = 0; i<20; i++){
				delete[] grille[i];								
			}

			delete[] grille;
		}

	
		bool isEmpty(int i, int j){ return grille[i][j].isEmpty(); }
		Block getBlock(int i, int j){ return grille[i][j];}

		void verify_ligne(){
			bool ligne_complete = true;
			for(int i = 0; i< 20; i++){

				for(int j = 0; j<10; j++){


					if( grille[i][j].isEmpty() ){ ligne_complete = false;}
				}

				if(ligne_complete == true){
					for(int j = 0; j<10; j++){


						grille[i][j].setState(true);
					}

				}


			ligne_complete = false;
			}

			for(int i = 19; i< 0; i--){

				for(int j = 0; j<10; j++){

					if(grille[i-1][j].isEmpty() == false && grille[i][j].isEmpty() == true ){


						grille[i][j].setState(true);
						grille[i-1][j].setState(false);}}
					}



		}

		void setTetriminos(Tetriminos * tetriminos){    

			current_Tetriminos = tetriminos;
		}

		Tetriminos * getTetriminos(){return current_Tetriminos;}

		bool isBlockLimit(){

			bool flag = false;

			for(int i =0; i<4; i++){
				
				if( current_Tetriminos->get_Y_block_of(i) == 19 
				    or grille[current_Tetriminos->get_Y_block_of(i)+1]
					         [current_Tetriminos->get_X_block_of(i)].isEmpty() == false ) 

					{flag =true;}




			}
			return flag;

		}

		void anchor_block(){

			for(int i =0; i<4; i++){
				
				grille[current_Tetriminos->get_Y_block_of(i)]
					  [current_Tetriminos->get_X_block_of(i)].setState(false);

				// grille[current_Tetriminos->get_Y_block_of(i)]
				// 	  [current_Tetriminos->get_X_block_of(i)].setState(false);

					

		}}
		



};