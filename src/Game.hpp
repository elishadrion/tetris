#include <unistd.h>
#include <thread>
#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <sys/time.h>

void player_choice(grid * maGrille){

	while(1){
		
		char ch = getch();
		if(ch == 'd'){
		(maGrille->getTetriminos())->move_right();}
		else if(ch == 'q'){
			(maGrille->getTetriminos())->move_left();
		}


	}




}

class Game{

	private:
		
		grid * maGrille;
		WINDOW *boite;
		int  template_tetriminos[7][4][2] ={
										 {{0,4}, {0,5}, {-1,4},{-1,5}},  // carré
										 {{0,3}, {0,4}, {0,5}, {0,6}},	 // barre
										 {{0,3},{-1,3}, {0,4}, {0,5}},   // L gauche
										 {{0,4}, {0,5}, {0,6}, {-1,6}},  // L droit
										 {{0,3}, {0,4}, {-1,4},{-1,5}},  // Z gauche
										 {{-1,4},{-1,5},{0,5}, {0,6}},   // Z droit
										 {{0,3}, {0,4}, {-1,4},{0,5}}    // T 
										};

	public:
		
		Game(){

			maGrille = new grid();

		}

		void init_window(){
    
  			
    		char *msg= "Texte au centre";
    		int taille= strlen(msg);
    
   			
    		while(1) {
        		clear();    // Efface la fenêtre (donc l'ancien message)
        		//boite= subwin(stdscr, 10, 10, LINES / 2, COLS /2);
        		mvprintw(2, 12, "TETRIS");

	   			boite= subwin(stdscr, 20+2, 10+2, 4, 10);
	   			


	    		//wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+');
	   
	    		box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut
	    		
        		refresh();
        		if(getch() != 410)
            		break;
   			}
    
    		
    
    
    
		}


		void update_well(Tetriminos * current_Tetriminos){

			for(int i =0; i<20; i++){
				
				for(int k=0; k<10; k++){
 
					if(current_Tetriminos->isBlockOfTetriminos(i,k)){
						mvprintw(5+i, 11+k, "x");
					}
					else if(maGrille->isEmpty(i,k) == false){
						mvprintw(5+i, 11+k, "x");
					}
					else{
						mvprintw(5+i, 11+k, " ");
					}
					
				}


				refresh();

				
			}




		}

		void start_Game(){

			srand(time(NULL));

			initscr();
			init_window();
			std::thread first (player_choice,maGrille);


			 while(1){
				Tetriminos * newTetriminos = new Tetriminos(template_tetriminos[rand()%(7-0)+0]);
				
				maGrille->setTetriminos(newTetriminos);
				
				
				update_well(newTetriminos);
				sleep(0.2);
				
				bool flag = false;
				while(not(flag)){
				
					
					newTetriminos->drop();
					maGrille->verify_ligne();
					update_well(newTetriminos);
					if(maGrille->isBlockLimit()){maGrille->anchor_block(); flag= true;}
					usleep(500000);

				}
				
				
			delete newTetriminos;
			
    		

			 
		}

		endwin();
    		
    		delete boite;
    		
			
			
}



};