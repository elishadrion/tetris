
#ifndef GAME_HPP
#define	GAME_HPP

#include <queue>
#include <vector>

#include "Player.hpp"
#include "PlayerInGame.hpp"


/**
 * One class per game.  Contain the two players and all other informations for
 * the game
 */
class Game {

    static std::queue<Player*> PlayerWaitGame;

    unsigned int _currentPlayer; // Player the must play now (0 or 1)
    unsigned int _turn;
    PlayerInGame* _player1;
    PlayerInGame* _player2;
    // Add log (file ?)


    Game(Player* p1, Player* p2);

    virtual void nextPlayer();
    void sendInformation();
    void sendInformation(PlayerInGame* player);
    PlayerInGame* getAdversePlayer(PlayerInGame* player);
    std::vector<Card*> getAdversePlacedCard(PlayerInGame* player);


public:
    //virtual void play();  // function when a player play. Call Listener.onPlayerPlay

    Game(); // Default constuctor
    Game(const Game&); // Copy constructor
    Game& operator=(const Game&); // Copy operator
    virtual ~Game() = default;


    static void addPlayerWaitGame(Player player); // Add a player to the PlayerWait list

};

std::queue<Player*> Game::PlayerWaitGame;



#endif	/* GAME_HPP */

