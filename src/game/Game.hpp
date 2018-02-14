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





class Game{

	private:
		
		Grid * grid;
		GUI * myGUI;
		
	

	public:
		
		Game();
		~Game();	
    	void init();
    	void start();
		
		// Mode de jeu
		void start_classic_game();
		void start_sprint_game();
		void start_marathon_game();

		int tetriminos_dropping();
		
    	
    



};

#endif
