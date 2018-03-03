#include "GameManager.hpp"
extern Game_CLI * display_game;
extern GameManager* game_manager;


void GameManager::start_game(unsigned _num,int type_game, unsigned seed){

	display_game = new Game_CLI();

	if(type_game==4){ 		
		_game = new Vs(seed);
		_game->init_game(true);
	}

	else if(type_game ==2){

		_game = new Marathon(seed);
		_game->init_game(true);
	}

	std::thread thread_joueur(player_get_choice_in_game, _game->get_grid(), _game->get_stopper());
	thread_joueur.join();  
	delete display_game;
	delete _game;
}




void player_get_choice_in_game(Grid* grid,Stopper_Thread* stopper) {

	int ch;
	bool flag;
	
	while(flag = !stopper->game_is_finish()){
		
		ch = getch();

		if  (flag and ch == KEY_RIGHT) {
			game_manager->move_right();
			grid->current_tetriminos_move_right();

		}
		else if (flag and ch == KEY_LEFT)  {
			game_manager->move_left();
			grid->current_tetriminos_move_left();
		}
		else if (flag and ch == 'd')       {
			game_manager->move_turn_right();
			grid->current_tetriminos_turn_right();
		}
		else if (flag and ch == 'q')       {
			game_manager->move_turn_left();
			grid->current_tetriminos_turn_left();
		}
		else if (flag and ch == 'z')       {
			game_manager->move_harddrop();
			grid->current_tetriminos_hard_drop();
		}
		else if (flag and ch == 'h')       {
			game_manager->move_hold();
			grid->set_current_tetriminos_hold();
		}
		else if (flag and ch ==  KEY_DOWN) {
			game_manager->move_drop();
			grid->set_acceleration_quick();
		}
	}
	WizardLogger::info("player_get_choice_in_game arrêté!");

}

void GameManager::move_right() {
	PacketManager::send_move_tetriminos(Packet::MOVE_TETRIMINOS_RIGHT);
}

void GameManager::move_left() {
	PacketManager::send_move_tetriminos(Packet::MOVE_TETRIMINOS_LEFT);
}

void GameManager::move_turn_right() {
	PacketManager::send_move_tetriminos(Packet::MOVE_TETRIMINOS_TURN_RIGHT);
}

void GameManager::move_turn_left() {
	PacketManager::send_move_tetriminos(Packet::MOVE_TETRIMINOS_TURN_LEFT);
}

void GameManager::move_hold() {
	PacketManager::send_move_tetriminos(Packet::MOVE_TETRIMINOS_HOLD);
}

void GameManager::move_harddrop() {
	PacketManager::send_move_tetriminos(Packet::MOVE_TETRIMINOS_HDROP);
}

void GameManager::move_drop() {
	PacketManager::send_move_tetriminos(Packet::MOVE_TETRIMINOS_DROP);
}