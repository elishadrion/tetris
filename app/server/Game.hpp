
#ifndef GAME_HPP
#define	GAME_HPP

#include <queue>
#include <vector>

#include "Player.hpp"
#include "PlayerInGame.hpp"


enum GameStatut {
    WAIT_DEC,
    IN_GAME
};



/**
 * One class per game.  Contain the two players and all other informations for
 * the game
 */
class Game {

    static std::queue<Player*> PlayerWaitGame;

    GameStatut _gameStatut;
    PlayerInGame* _currentPlayer; // Player the must play now (0 or 1)
    unsigned int _turn;
    PlayerInGame* _player1;
    PlayerInGame* _player2;
    // Add log (file ?)


    Game(Player* p1, Player* p2);

    virtual void nextPlayer();
    bool isInGame();
    void sendInformation();
    void sendInformation(PlayerInGame*,dataIGPlayer, dataIGPlayer);
    PlayerInGame* getAdversePlayer(PlayerInGame* player);
    std::vector<Card*> getAdversePlacedCard(PlayerInGame* player);


public:
    //virtual void play();  // function when a player play. Call Listener.onPlayerPlay

    Game(); // Default constuctor
    Game(const Game&); // Copy constructor
    Game& operator=(const Game&); // Copy operator
    virtual ~Game() = default;
    void draw();

    void checkDeckAndStart();


    static void addPlayerWaitGame(Player player); // Add a player to the PlayerWait list

};



#endif	/* GAME_HPP */

