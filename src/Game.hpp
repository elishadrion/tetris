/*
Groupe 2 : 3V-CUBE

Game.hpp
*/

#ifndef __GAME__HPP__
#define __GAME__HPP__

#include <unistd.h>
#include <thread>
#include <string.h>
#include <sys/time.h>
#include "GUI.hpp"
#include "Grid.hpp"





class Game{

	private:
		
		Grid * grid;
		GUI * myGUI; 
		
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
		
		Game();
		~Game();	
    
    	void start();
		
		void start_Game();
		
    		
    



};

#endif