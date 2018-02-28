#include "GameManager.hpp"
extern vsGUI *gui;
extern GameManager* game_manager;


void GameManager::create_game(unsigned _num, unsigned seed){
	gui = new vsGUI();    
	_game = new Vs(seed);
    _game->init_game(true);
	std::thread thread_joueur(player_get_choice_in_game, _game->get_grid());
	thread_joueur.join();	
	delete gui;
	delete _game;
}

void player_get_choice_in_game(Grid* grid) {
	int ch;
	while(!game_manager->get_game()->get_is_finished()){
		
		ch = getch();

		if      (ch == KEY_RIGHT) {
			game_manager->move_right();
			grid->current_tetriminos_move_right();

		}
		else if (ch == KEY_LEFT)  {
			game_manager->move_left();
			grid->current_tetriminos_move_left();
		}
		else if (ch == 'd')       {
			game_manager->move_turn_right();
			grid->current_tetriminos_turn_right();
		}
		else if (ch == 'q')       {
			game_manager->move_turn_left();
			grid->current_tetriminos_turn_left();
		}
		else if (ch == 'z')       {
			game_manager->move_harddrop();
			grid->current_tetriminos_hard_drop();
		}
		else if (ch == 'h')       {
			game_manager->move_hold();
			grid->set_current_tetriminos_hold();
		}
		else if (ch ==  KEY_DOWN) {
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