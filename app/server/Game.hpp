
#ifndef GAME_HPP
#define	GAME_HPP

#include <queue>
#include <vector>

#include "Player.hpp"
#include "PlayerInGame.hpp"
#include "common/WizardLogger.hpp"

#include "common/Error.hpp"


enum GameStatut {
    WAIT_DEC,
    IN_GAME
};



/**
 * One class per game.  Contains the two players and all other information for
 * the game
 */
class Game {

    static std::queue<Player*> PlayerWaitGame;

    GameStatut _gameStatut;
    PlayerInGame* _currentPlayer; // Player that must play now (0 or 1)
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
    PlayerInGame* getAdversePlayer();
    std::vector<CardMonster*> getAdversePlacedCard(PlayerInGame* player);


public:
    //virtual void play();  // function when a player plays. Calls Listener.onPlayerPlay

    Game(); // Default constuctor
    Game(const Game&); // Copy constructor
    Game& operator=(const Game&); // Copy operator
    virtual ~Game() = default;

    // Function before the game
    void checkDeckAndStart();
    static void addPlayerWaitGame(Player player); // Adds a player to the PlayerWait list

    // Function during the game
    void draw(); // current player draw a card
    Error placeCard(PlayerInGame*, Card*, CardMonster*);
    Error placeCard(PlayerInGame*, Card*, PlayerInGame*);
    Error attackWithCard(PlayerInGame*, CardMonster*, CardMonster*);
    Error attackWithCard(PlayerInGame*, CardMonster*, PlayerInGame*);


private:
    void beginTurn(); // function when the turn begin
    void endTurn();

    Error canPlayerAttack(PlayerInGame*,CardMonster*);
    bool verifyTaunt(PlayerInGame*,CardMonster*);
    bool verifyTaunt(PlayerInGame*);
    bool havePlace(PlayerInGame*);

    Error placeCard(PlayerInGame*, Card*);
    Error attackWithCard(PlayerInGame*,CardMonster*);

};



#endif	/* GAME_HPP */

