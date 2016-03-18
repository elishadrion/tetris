
#ifndef GAME_HPP
#define	GAME_HPP

#include <vector>

#include "Player.hpp"
#include "PlayerInGame.hpp"
#include "CardMonster.hpp"

#include "PacketManager.hpp"
#include "common/WizardLogger.hpp"
#include "common/Error.hpp"
#include "common/Constants.hpp"


enum GameStatut {
    WAIT_DEC,
    IN_GAME
};



/**
 * One class per game.  Contains the two players and all other information for
 * the game
 */
class Game {

    static std::vector<Player*> PlayerWaitGame;

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


public:
    Game(); // Default constuctor
    Game(const Game&); // Copy constructor
    Game& operator=(const Game&) = default; // Copy operator
    ~Game();

    // Function before the game
    void checkDeckAndStart();
    static void addPlayerWaitGame(Player *player); // Adds a player to the PlayerWait list
    static void removePlayerWaitGame(Player *player); // Remove player to the PlayerWait list

    // Function during the game
    void draw(); // current player draw a card
    void draw(PlayerInGame*); // current player draw a card
    Error placeCardAffectPlayer(PlayerInGame*, Card*);
    Error placeCard(PlayerInGame*, CardMonster*);
    Error placeCard(PlayerInGame*, Card*, CardMonster*);
    Error attackWithCard(PlayerInGame*, CardMonster*, CardMonster*);
    Error attackWithCardAffectPlayer(PlayerInGame*, CardMonster*);
    void nextPlayer();

    void sendInfoAction(std::string, int, int, unsigned, bool, bool);


private:
    void beginTurn(); // function when the turn begin
    void endTurn();

    // During the game
    Error canPlayerAttack(PlayerInGame*,CardMonster*);
    bool verifyTaunt(PlayerInGame*,CardMonster*);
    bool verifyTaunt(PlayerInGame*);
    bool havePlace(PlayerInGame*);
    void isPlayerInLife();
    void isPlayerInLife(PlayerInGame* pIG);

    int getRealPosition(PlayerInGame*, int);
    int getRelativePosition(PlayerInGame*, int);
    Error canPlaceCard(PlayerInGame*, Card*);
    void endParty(PlayerInGame*);

};



#endif	/* GAME_HPP */

