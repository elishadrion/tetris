/*
Groupe 2 : 3V-CUBE

vsGUI.cpp
*/
#include "Game_CLI.hpp"
#include <sys/time.h>



Game_CLI::Game_CLI(){ 

	clear();
	init_colors();

}


Game_CLI::~Game_CLI(){ 

	delwin(BOX_HOLD_TETRIMINOS);
	delwin(BOX_NEXT_TETRIMINOS);
	delwin(BOX_GRID_PLAYER);
	delwin(BOX_NEXT_TETRIMINOS_OTHER);
	delwin(BOX_HOLD_TETRIMINOS_OTHER);
	delwin(BOX_NEXT_TETRIMINOS_OTHER);
	

}


void Game_CLI::init_colors() {

	
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


void Game_CLI::init_main_game_solo_GUI(){
	/*
	Cette fonction affiche toute l'interface du jeu fonctionel de tetris.
	*/		

	
		BOX_GRID_PLAYER = subwin(stdscr,23,24,1,9+10);
	    box(BOX_GRID_PLAYER, ACS_VLINE, ACS_HLINE);
		attron(A_BOLD | COLOR_PAIR(8));	

		// Création de la grille de jeu
	   	
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

}

void Game_CLI::init_main_game_multi_GUI(){
	

		BOX_GRID_PLAYER = subwin(stdscr,23,24,1,5+10);
	    box(BOX_GRID_PLAYER, ACS_VLINE, ACS_HLINE);
		attron(A_BOLD | COLOR_PAIR(8));	

		BOX_GRID_OTHER = subwin(stdscr,23,24,1,30+11);
	    box(BOX_GRID_OTHER, ACS_VLINE, ACS_HLINE);
		attron(A_BOLD | COLOR_PAIR(8));	


	   	// Création box du prochain tétriminos

	   	
	    BOX_NEXT_TETRIMINOS = subwin(stdscr,5,13,12,1);
	    box(BOX_NEXT_TETRIMINOS, ACS_VLINE, ACS_HLINE);
	    mvprintw(16, 6, "Next");

	    
	    BOX_HOLD_TETRIMINOS = subwin(stdscr,5,13,17,1);
	    box(BOX_HOLD_TETRIMINOS, ACS_VLINE, ACS_HLINE);
	    mvprintw(19, 7, "Hold");

	    BOX_NEXT_TETRIMINOS_OTHER = subwin(stdscr,5,13,3,66);
	    box(BOX_NEXT_TETRIMINOS_OTHER, ACS_VLINE, ACS_HLINE);
	    mvprintw(7, 71, "Next");

	    
	    BOX_HOLD_TETRIMINOS_OTHER = subwin(stdscr,5,13,9,66);
	    box(BOX_HOLD_TETRIMINOS_OTHER, ACS_VLINE, ACS_HLINE);
	    mvprintw(13, 71, "Hold");

	    mvprintw(10, 39, "VS");


	    attron(A_BOLD | COLOR_PAIR(8));	
		mvprintw(3, 1, "LEVEL :");
		mvprintw(5, 1, "SCORE :");
		mvprintw(7, 1, "LINES :");

		mvprintw(16, 66, "LEVEL :");
		mvprintw(18, 66, "SCORE :");
		mvprintw(20, 66, "LINES :");	

		refresh();
}




void Game_CLI::update_main_game_multi_GUI(Grid * grid, Grid * other_grid){
	/*
	On met à jour l'affichage de la grille du jeu.
		:param grid: Grid*
	*/

	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(5, 8,"%d", grid->get_score());
	mvprintw(3, 8,"%d", grid->get_level());
	mvprintw(7, 8,"%d", grid->get_line_complete());

	mvprintw(16, 73,"%d", other_grid->get_score());
	mvprintw(18, 73,"%d", other_grid->get_level());
	mvprintw(20, 73,"%d", other_grid->get_line_complete());

	for(int i =0; i < 20; i++){
		
		for(int j=0; j < 10; j++){
			
			
			// Si on affiche un ancien block de tétriminos.
			if(grid->is_empty(i,j) == false){
				
				attron(A_BOLD | COLOR_PAIR(grid->get_color_of_block(i,j)));	
				mvprintw(3+i, 17+j*2, "  ");
			}

			// Si on affiche un bloc du tétriminos.
			else if(grid->get_tetriminos()->has_block(i,j)){
				
				attron(A_BOLD | COLOR_PAIR(grid->get_color_of_tetriminos()));	
				mvprintw(3+i, 17+j*2, "  ");
			}
			// Si on affiche tout autre block.
			else{
				
				attron(A_BOLD | COLOR_PAIR(8));	
				mvprintw(3+i, 17+j*2, "  ");
			}	



			if(other_grid->is_empty(i,j) == false){
				
				attron(A_BOLD | COLOR_PAIR(other_grid->get_color_of_block(i,j)));	
				mvprintw(3+i, 43+j*2, "  ");
			}

			// Si on affiche un bloc du tétriminos.
			else if(other_grid->get_tetriminos()->has_block(i,j)){
				
				attron(A_BOLD | COLOR_PAIR(other_grid->get_color_of_tetriminos()));	
				mvprintw(3+i, 43+j*2, "  ");
			}
			// Si on affiche tout autre block.
			else{
				
				attron(A_BOLD | COLOR_PAIR(8));	
				mvprintw(3+i, 43+j*2, "  ");
			}			
			
				
		}
					
	}
	refresh();
		
}


void Game_CLI::erase_hold_tetriminos_solo_GUI(){
	/*
	Effacemment du hold tetréminos sur la GUI.
	*/

	wclear(BOX_HOLD_TETRIMINOS);	
	box(BOX_HOLD_TETRIMINOS, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(11, 54, "Hold");
	wrefresh(BOX_HOLD_TETRIMINOS);

}

void Game_CLI::erase_next_tetriminos_solo_GUI(){
	/*
	Effacemment du prochain tetréminos sur la vsGUI.
	*/

	werase(BOX_NEXT_TETRIMINOS);	
	box(BOX_NEXT_TETRIMINOS, ACS_VLINE, ACS_HLINE);	 
	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(5, 54, "Next");
	wrefresh(BOX_NEXT_TETRIMINOS);


}

void Game_CLI::erase_next_tetriminos_multi_GUI(){
	/*
	Effacemment du prochain tetréminos sur la vsGUI.
	*/

	werase(BOX_NEXT_TETRIMINOS);	
	box(BOX_NEXT_TETRIMINOS, ACS_VLINE, ACS_HLINE);	 
	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(16, 6, "Next");
	wrefresh(BOX_NEXT_TETRIMINOS);	

}

void Game_CLI::erase_hold_tetriminos_other_GUI(){
	/*
	Effacemment du hold tetréminos sur la vsGUI.
	*/

	werase(BOX_HOLD_TETRIMINOS_OTHER);		
	box(BOX_HOLD_TETRIMINOS_OTHER, ACS_VLINE, ACS_HLINE);	
	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(13, 71, "Hold");
	wrefresh(BOX_HOLD_TETRIMINOS_OTHER);

}

void Game_CLI::erase_hold_tetriminos_multi_GUI(){
	/*
	Effacemment du hold tetréminos sur la vsGUI.
	*/

	werase(BOX_HOLD_TETRIMINOS);		
	box(BOX_HOLD_TETRIMINOS, ACS_VLINE, ACS_HLINE);	
	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(19, 7, "Hold");
	wrefresh(BOX_HOLD_TETRIMINOS);

}

void Game_CLI::erase_next_tetriminos_other_multi_GUI(){

	werase(BOX_NEXT_TETRIMINOS_OTHER);	
	box(BOX_NEXT_TETRIMINOS_OTHER, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD | COLOR_PAIR(8));	
	mvprintw(7, 71, "Next");
	wrefresh(BOX_NEXT_TETRIMINOS_OTHER);





}
void Game_CLI::update_next_tetriminos_multi_GUI(Tetriminos * next_tetriminos, Tetriminos * next_tetriminos_other){

	/*
	On affiche le hold tétriminos sur la vsGUI.
		:param grid: Grid *
	*/

	erase_next_tetriminos_multi_GUI();
	erase_next_tetriminos_other_multi_GUI();


	int x,y;
	for(int i=0; i<4; i++){
	
		y = next_tetriminos->get_coord_Y_of_block(i);
		x = next_tetriminos->get_coord_X_of_block(i);

		attron(A_BOLD | COLOR_PAIR(next_tetriminos->get_color_of_block(0)));
		mvprintw( 14+y,-2+x*2 , "  ");

		y = next_tetriminos_other->get_coord_Y_of_block(i);
        x = next_tetriminos_other->get_coord_X_of_block(i);

		attron(A_BOLD | COLOR_PAIR(next_tetriminos_other->get_color_of_block(0)));
		mvprintw( 5+y,63+x*2 , "  ");
	}


}

void Game_CLI::update_hold_tetriminos_solo_GUI(Tetriminos * hold_tetriminos){
	/*
	On affiche le hold tétriminos sur la vsGUI.
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

void Game_CLI::update_hold_tetriminos_multi_GUI(Tetriminos * hold_tetriminos){
	/*
	On affiche le hold tétriminos sur la vsGUI.
		:param grid: Grid *
	*/	

		
	int x,y;
	for(int i=0; i<4; i++){			
		
		y = hold_tetriminos->get_coord_Y_of_block(i);
		x = hold_tetriminos->get_coord_X_of_block(i);

		attron(A_BOLD | COLOR_PAIR(hold_tetriminos->get_color_of_block(0)));
		mvprintw( 19+y,-2+x*2 , "  ");
	}


	

}




void Game_CLI::update_hold_tetriminos_other_GUI(Tetriminos* hold_tetriminos_other){
	/*
	On affiche le hold tétriminos sur la vsGUI.
		:param grid: Grid *
	*/
		
		int x, y;
		for(int i=0; i<4; i++){			


			y = hold_tetriminos_other->get_coord_Y_of_block(i);
			x = hold_tetriminos_other->get_coord_X_of_block(i);

			attron(A_BOLD | COLOR_PAIR(hold_tetriminos_other->get_color_of_block(0)));
			mvprintw( 11+y,63+x*2 , "  ");

		}


}

void Game_CLI::update_next_tetriminos_solo_GUI(Tetriminos * next_tetriminos){

	/*
	On affiche le hold tétriminos sur la GUI.
		:param grid: Grid *
	*/

	erase_next_tetriminos_solo_GUI();

	for(int i=0; i<4; i++){

		int y = next_tetriminos->get_coord_Y_of_block(i);
		int x = next_tetriminos->get_coord_X_of_block(i);

		attron(A_BOLD | COLOR_PAIR(next_tetriminos->get_color_of_block(0)));
		mvprintw( 3+y,46+x*2 , "  ");
	}


}




void Game_CLI::update_main_game_solo_GUI(Grid * grid){
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