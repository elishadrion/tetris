
#ifndef GAME_HPP
#define	GAME_HPP

#include <vector>
#include "Player.hpp"
#include "PlayerInGame.hpp"


/**
 * One class per game.  Contain the two players and all other informations for
 * the game
 */
class Game {

    static std::vector<Player*> PlayerWaitGame;



    Game(Player p1, Player p2);

    PlayerInGame* _player1;
    PlayerInGame* _player2;
    int currentPlayer = 1; // Player the must play now (0 or 1)
    // Add log (file ?)


    virtual void nextPlayer();


public:
    //virtual void play();  // function when a player play. Call Listener.onPlayerPlay

    virtual ~Game() = default;


    static void findAdversary(Player player); // Find a other player to play a game

};

std::vector<Player*> Game::PlayerWaitGame;



#endif	/* GAME_HPP */

