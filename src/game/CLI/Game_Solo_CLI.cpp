/*
Groupe 2 : 3V-CUBE

GUI.cpp
*/
#include "Game_Solo_CLI.hpp"



Game_Solo_CLI::Game_Solo_CLI(){ 

	initscr();   // première routine à appelé avant d'initialiser un programme.
	noecho();    // On cache les inputs du terminal.
	curs_set(0); // On cache le curseur
	keypad(stdscr, TRUE); // On permet d'utiliser le keypad
	init_colors();
}


Game_Solo_CLI::~Game_Solo_CLI(){ 

	delwin(BOX_GRID);
	delwin(BOX_NEXT_TETRIMINOS);
	delwin(BOX_HOLD_TETRIMINOS);

	endwin();

}


void Game_Solo_CLI::init_colors() {

	start_color();
	assume_default_colors(COLOR_WHITE,-1);
	
	init_pair(1, -1, COLOR_RED);
	init_pair(2, -1, COLOR_GREEN);
	init_pair(3, -1, COLOR_YELLOW);
	init_pair(4, -1, COLOR_BLUE);
	init_pair(5, -1, COLOR_MAGENTA);
	init_pair(6, -1, COLOR_CYAN);
	init_pair(7, -1, COLOR_WHITE);
	init_pair(8, -1, -1);	
	init_pair(9, -1, COLOR_BLACK);
	
}



// void GUI::init_window_GUI(){
// 	/*
// 	Cette fonction permet d'afficher un menu permettant à l'utilisateur de 
// 	choisir de jouer une partie ou bien de changer les touches du jeu.
// 	*/

// 	const int CHOICE_NB = 2;
//  	const std::string CHOICES[CHOICE_NB]={"Play game", "Settings"};

//  	int choice;
//  	int highlights =0;

// 	char *msg= "TETRIS";
//     int taille= strlen(msg);

//     clear();    // Efface la fenêtre (donc l'ancien message)
//     attron(A_BOLD );
//     mvprintw(5, (COLS / 2) - (taille / 2), "TETRIS");
 	
// 	while(1){

// 	 	for(int i =0; i < CHOICE_NB; i++){

// 	 		if(i==highlights)
// 	 			attron(A_REVERSE);		

// 			mvprintw(0,i*10,CHOICES[i].c_str());
// 			attroff(A_REVERSE);

// 	 	}
// 	 	choice = getch();

// 		switch(choice){

// 			case KEY_UP:
// 				highlights--;
// 				if (highlights==-1){
// 					highlights=0;
// 				}
// 				break;

// 			case KEY_DOWN:
// 				highlights++;
// 				if(highlights==2){
// 					highlights =1;
// 				}
// 				break;

// 			default:
// 				break;
// 		}

// 		if (choice==10){
// 			break;
// 		}


// 	 }
				
// }


void Game_Solo_CLI::init_main_game_GUI(){
	/*
	Cette fonction affiche toute l'interface du jeu fonctionel de tetris.
	*/		


	BOX_GRID = subwin(stdscr,23,24,1,9+10);
    box(BOX_GRID, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD | COLOR_PAIR(8));	

	// Création de la grille de jeu
	
	int i,j;
    for(i=0; i < 20 ; i++){
        for(j=0; j < 22 ; j+=2){
        	
            mvprintw(i+3,j+20,"  ");
        }
    }
   	
   	// Création box du prochain tétriminos

   	
    BOX_NEXT_TETRIMINOS = subwin(stdscr,5,13,1,49);
    box(BOX_NEXT_TETRIMINOS, ACS_VLINE, ACS_HLINE);
    mvprintw(5, 54, "Next");

    
    BOX_HOLD_TETRIMINOS = subwin(stdscr,5,13,7,49);
    box(BOX_HOLD_TETRIMINOS, ACS_VLINE, ACS_HLINE);
    mvprintw(11, 54, "Hold");
    
    attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(3, 3, "LEVEL :");
	mvprintw(5, 3, "SCORE :");
	mvprintw(12, 3, "LINES :");

	refresh();
}



void Game_Solo_CLI::update_main_game_GUI(Grid * grid){
	/*
	On met à jour l'affichage de la grille du jeu.
		:param grid: Grid*
	*/

	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(5, 11,"%d", grid->get_score());
	mvprintw(3, 11,"%d", grid->get_level());
	mvprintw(12, 11,"%d", grid->get_line_complete());

	for(int i =0; i < 20; i++){
		
		for(int j=0; j < 10; j++){

			// Si on affiche un bloc du tétriminos.
			if(grid->get_tetriminos()->has_block(i,j)){
				
				attron(A_BOLD | COLOR_PAIR(grid->get_color_of_tetriminos()));	
				mvprintw(3+i, 21+j*2, "  ");
			}
			// Si on affiche un ancien block de tétriminos.
			else if(grid->is_empty(i,j) == 0){
				
				attron(A_BOLD | COLOR_PAIR(grid->get_color_of_block(i,j)));	
				mvprintw(3+i, 21+j*2, "  ");
			}
			// Si on affiche tout autre block.
			else{
				
				attron(A_BOLD | COLOR_PAIR(8));	
				mvprintw(3+i, 21+j*2, "  ");
			}
				
		}
					
	}
	refresh();	
}




void Game_Solo_CLI::erase_next_tetriminos_GUI(){
	/*
	Effacemment du prochain tetréminos sur la GUI.
	*/

	werase(BOX_NEXT_TETRIMINOS);	
	box(BOX_NEXT_TETRIMINOS, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(5, 54, "Next");
	wrefresh(BOX_NEXT_TETRIMINOS);

}

void Game_Solo_CLI::erase_hold_tetriminos_GUI(){
	/*
	Effacemment du hold tetréminos sur la GUI.
	*/

	werase(BOX_HOLD_TETRIMINOS);	
	box(BOX_HOLD_TETRIMINOS, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(11, 54, "Hold");
	wrefresh(BOX_HOLD_TETRIMINOS);

}

void Game_Solo_CLI::update_next_tetriminos_GUI(Tetriminos * next_tetriminos){

	/*
	On affiche le hold tétriminos sur la GUI.
		:param grid: Grid *
	*/

	erase_next_tetriminos_GUI();

	for(int i=0; i<4; i++){

		int y = next_tetriminos->get_coord_Y_of_block(i);
		int x = next_tetriminos->get_coord_X_of_block(i);

		attron(A_BOLD | COLOR_PAIR(next_tetriminos->get_color_of_block(0)));
		mvprintw( 3+y,46+x*2 , "  ");
	}


}

void Game_Solo_CLI::update_hold_tetriminos_GUI(Tetriminos * hold_tetriminos){
	/*
	On affiche le hold tétriminos sur la GUI.
		:param grid: Grid *
	*/

	if(hold_tetriminos !=nullptr){
		
		for(int i=0; i<4; i++){

			
			int y = hold_tetriminos->get_coord_Y_of_block(i);
			int x = hold_tetriminos->get_coord_X_of_block(i);

			attron(A_BOLD | COLOR_PAIR(hold_tetriminos->get_color_of_block(0)));
			mvprintw( 9+y,46+x*2 , "  ");
		}

	}

}


