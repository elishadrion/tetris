#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

class GameManager;

#include <vector>
#include <string>

#include "../common/Constants.hpp"
#include "../common/WizardLogger.hpp"
#include "PacketManager.hpp"

#include "../game/Mode/Mode.hpp"
#include "../game/Game_system/Grid.hpp"
#include "../game/Mode/Vs.hpp"
#include "../game/GUI/vsGUI.hpp"

void player_get_choice_in_game(Grid *);

class GameManager {
	Mode * _game;
	public:
	    GameManager() = default;
	    void create_game(unsigned, unsigned);
	    void move_right();
	    void move_left();
	    void move_turn_right();
	    void move_turn_left();
	    void move_hold();
	    void move_harddrop();
	    void move_drop();
	    Mode * get_game(){return _game;}

};




#endif // GAMEMANAGER_HPP
