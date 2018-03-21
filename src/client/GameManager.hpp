#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

class GameManager;

#include <vector>
#include <string>

#include "../common/Constants.hpp"
#include "../common/WizardLogger.hpp"
#include "PacketManager.hpp"

#include "GUI/Board_GUI.hpp"
#include "CLI/Board_CLI.hpp"

#include "../game/Game_system/Grid.hpp"
#include "../game/Mode/Vs.hpp"
#include "../game/Mode/Marathon.hpp"
#include "../game/Mode/Sprint.hpp"
#include "../game/Mode/Classic.hpp"





class GameManager {
	Mode * _game;
	bool gui;
	public:
	    GameManager(bool _gui): gui(_gui) {}
	    void start_game(unsigned,int, unsigned);
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
