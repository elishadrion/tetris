#include "GameManager.hpp"


extern GameManager* game_manager;

info_game GameManager::start_game(long _num,int type_game, long seed){
	
	
	if     (type_game == 1){ _game = new Classic(seed);}
	else if(type_game == 2){ _game = new Marathon(seed);}
	else if(type_game == 3){ _game = new Sprint(seed);}
	else if(type_game == 4){ _game = new Vs(seed);}
	
	   
	_game->init_game(true);
	
	WizardLogger::info("game lancé!");
	
	if (gui) {

		Board_GUI * display_game = new Board_GUI(type_game == 4, 800, 600, _game->get_grid(), _game->get_other_grid());
		display_game->start();
	
		while(!_game->get_stopper()->game_is_finish()){}
		usleep(50000);
		delete display_game;

	} else {

		Board_CLI * display_game = new Board_CLI(_game->get_grid(), _game->get_other_grid(),_game->get_stopper());
		display_game->start(type_game);
		
		while(!_game->get_stopper()->game_is_finish()){}
		usleep(200000);
		delete display_game;

	}

	struct info_game myInfo;
	myInfo.winner= _game->is_winner();
	myInfo.score = _game->get_grid()->get_score();
	myInfo.line_complete = _game->get_grid()->get_line_complete();
	myInfo.level = _game->get_grid()->get_level();
	
	delete _game;
	return myInfo;

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
