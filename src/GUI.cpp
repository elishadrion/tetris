/*
Groupe 2 : 3V-CUBE

GUI.cpp
*/
#include "GUI.hpp"


GUI::GUI(){}
GUI::~GUI(){delete boite;}


void GUI::init_window_GUI(){

 	
			
	

	}


void GUI::window_grid_GUI(){

	char *msg = "Texte au centre";
	int taille = strlen(msg);

		
	while(1) {
		clear(); 
		
		mvprintw(2, 12, "TETRIS");

			boite= subwin(stdscr, 20+2, 10+2, 4, 10);


		box(boite, ACS_VLINE, ACS_HLINE); // ACS_VLINE et ACS_HLINE sont des constantes qui génèrent des bordures par défaut
		
		refresh();
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
