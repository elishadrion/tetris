
#ifndef GAME_HPP
#define	GAME_HPP

#include <queue>
#include <vector>

#include "Player.hpp"
#include "PlayerInGame.hpp"
#include "CardMonster.hpp"

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

    // Attribut
    GameStatut _gameStatut;
    PlayerInGame* _currentPlayer; // Player that must play now (0 or 1)
    unsigned int _turn;
    PlayerInGame* _player1;
    PlayerInGame* _player2;

    // Constructor
    Game(Player* p1, Player* p2);

    bool isInGame();
    //void sendInformation(); // Not use
    //void sendInformation(PlayerInGame*,dataIGPlayer, dataIGPlayer); // Not use
    PlayerInGame* getAdversePlayer(PlayerInGame* player);
    PlayerInGame* getAdversePlayer();
    std::vector<CardMonster*> getAdversePlacedCard(PlayerInGame* player);


public:
    //virtual void play();  // function when a player plays. Calls Listener.onPlayerPlay

    Game(); // Default constuctor
    Game(const Game&); // Copy constructor
    Game& operator=(const Game&) = default; // Copy operator
    virtual ~Game() = default;

    // Function before the game
    void checkDeckAndStart();
    static void addPlayerWaitGame(Player player); // Adds a player to the PlayerWait list

    // Function during the game
    void draw(); // current player draw a card
    void draw(PlayerInGame*); // current player draw a card
    Error placeCardAffectPlayer(PlayerInGame*, Card*);
    Error placeCard(PlayerInGame*, Card*, CardMonster*);
    Error attackWithCard(PlayerInGame*, CardMonster*, CardMonster*);
    Error attackWithCardAffectPlayer(PlayerInGame*, CardMonster*);
    void nextPlayer();

    void sendInfoAction(PlayerInGame*,int,unsigned int);


private:
    void beginTurn(); // function when the turn begin
    void endTurn();

    // Function to InitGame
    //void sendInitInfo();
    //void sendInitInfo(PlayerInGame*);

    // During the game
    Error canPlayerAttack(PlayerInGame*,CardMonster*);
    bool verifyTaunt(PlayerInGame*,CardMonster*);
    bool verifyTaunt(PlayerInGame*);
    bool havePlace(PlayerInGame*);
    void isPlayerInLife();
    void isPlayerInLife(PlayerInGame* pIG);

    Error placeCard(PlayerInGame*, Card*);

};



#endif	/* GAME_HPP */

