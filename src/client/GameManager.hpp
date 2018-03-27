#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

class GameManager;
struct info_game;

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


struct info_game{

    bool winner;
    int score;
    int level;
    int line_complete;
    int time;
};


class GameManager {


	Mode * _game;
	bool gui;
	public:
	    GameManager(bool _gui): gui(_gui) {}
	    info_game start_game(long,int, long);
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
