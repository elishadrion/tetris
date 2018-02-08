/*
Groupe 2 : 3V-CUBE

GUI.cpp
*/
#include "GUI.hpp"


GUI::GUI(){ initscr(); // première routine à appelé avant d'initialiser un programme.

			noecho();    // On cache les inputs du terminal.
			
			keypad(stdscr, TRUE);
		  }
GUI::~GUI(){endwin();delwin(boite);}


void GUI::init_window_GUI(){

 	
			
	

	}


void GUI::window_grid_GUI(){

	char *msg = "Texte au centre";
	int taille = strlen(msg);

		
	
	clear(); 
	
	mvprintw(2, 12, "TETRIS");

	boite = subwin(stdscr, 20+2, 10+2, 4, 10);


	box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut
	
	refresh();
	while(1) {
		if(getch() != 410)
			break;
	}






}



void GUI::update_grid_GUI(Grid * grid){

	for(int i =0; i<20; i++){
		
		for(int k=0; k<10; k++){

			if(grid->getTetriminos()->hasBlock(i,k)){
				mvprintw(5+i, 11+k, "x");
			}

			else if(grid->isEmpty(i,k) == false){
				mvprintw(5+i, 11+k, "x");
			}

			else{
				mvprintw(5+i, 11+k, " ");
			}
			
		}




		refresh();

		
	}

	mvprintw(0, 0, "");

	refresh();




}
