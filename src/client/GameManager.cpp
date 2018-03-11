#include "GameManager.hpp"

extern Game_CLI * display_game;
extern GameManager* game_manager;
extern Board* display_game_gui;


void GameManager::start_game(unsigned _num,int type_game, unsigned seed){

	if(type_game==1){ 		
		_game = new Classic(seed);
		_game->init_game(true);
	}

	else if(type_game ==2){

		_game = new Marathon(seed);
		_game->init_game(true);
	}
	else if(type_game ==3){

		_game = new Sprint(seed);
		_game->init_game(true);
	}

	else if(type_game ==4){

		_game = new Vs(seed);
		_game->init_game(true);
	}

	if (gui) {
		display_game_gui = new Board(type_game == 4, 800, 600, _game->get_grid(), _game->get_other_grid());
		display_game_gui->start();
		while (!_game->get_stopper()->game_is_finish());
	} else {
		display_game = new Game_CLI();
		std::thread thread_joueur(player_get_choice_in_game, _game->get_grid(), _game->get_stopper());
		thread_joueur.join();
	}

	if (!gui)
		delete display_game;
	delete _game;
}



void player_get_choice_in_game(Grid* grid,Stopper_Thread* stopper) {
    
    char C_rotateRigth;
    char C_rotateLeft;
    char C_accelerate;
    char C_moveRigth;
    char C_moveLeft;
    char C_hardDrop;
    char C_hold;
    
    const csv::Parser file = csv::Parser("./settings/keys_settings.csv");
    int lineNumber = file.rowCount();

    for (int i = 0; i < lineNumber; i++) {
        std::string keyValue = file[i]["key"];
        int keyNumber = static_cast<char>(std::stoi(file[i]["key_id"]));

        if (keyValue == "rotateRigth"){
        C_rotateRigth = keyNumber;
        }
        else if (keyValue == "rotateLeft"){
        C_rotateLeft = keyNumber;
        }
        else if (keyValue == "accelerate"){
        C_accelerate = keyNumber;
        }
        else if (keyValue == "moveRigth"){
        C_moveRigth = keyNumber;
        }
        else if (keyValue == "moveLeft"){
        C_moveLeft = keyNumber;
        }
        else if (keyValue == "hardDrop"){
        C_hardDrop = keyNumber;
        }
        else if (keyValue == "hold"){
        C_hold = keyNumber;
        }
    }
    
	int ch;
	bool flag;
	
	while(flag = !stopper->game_is_finish()){
		
		ch = getch();
		flag = !stopper->game_is_finish();
		if  (flag and ch == C_moveRigth) {
			game_manager->move_right();
			grid->current_tetriminos_move_right();

		}
		else if (flag and ch == C_moveLeft)  {
			game_manager->move_left();
			grid->current_tetriminos_move_left();
		}
		else if (flag and ch == C_rotateRigth) {
			game_manager->move_turn_right();
			grid->current_tetriminos_turn_right();
		}
		else if (flag and ch == C_rotateLeft) {
			game_manager->move_turn_left();
			grid->current_tetriminos_turn_left();
		}
		else if (flag and ch == C_hardDrop)       {
			game_manager->move_harddrop();
			grid->current_tetriminos_hard_drop();
		}
		else if (flag and ch == C_hold)       {
			game_manager->move_hold();
			grid->set_current_tetriminos_hold();
		}
		else if (flag and ch ==  C_accelerate) {
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
