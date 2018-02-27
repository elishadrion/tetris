#include "GameManager.hpp"
extern vsGUI *gui;
extern GameManager* game_manager;

GameManager::GameManager(unsigned seed): _seed(seed) {}

void GameManager::create_game(unsigned _num){

	gui = new vsGUI();    
	_game = new Vs();

    _game->init_game(true);


	

		std::thread thread_joueur(player_get_choice_in_game, _game->get_grid());
		thread_joueur.detach();	



	while(1){};
	
}

void player_get_choice_in_game(Grid* grid) {
	int ch;
	while(1){
		
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