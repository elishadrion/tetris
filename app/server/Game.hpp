
#ifndef GAME_HPP
#define	GAME_HPP

/**
 * One class per game.  Contain the two players and all other informations for
 * the game
 */
class Game {

    Game(Player p1, Player p2);

    PlayerInGame _player1;
    PlayerInGame _player2;
    int currentPlayer; // Player the must play now (1 or 2)
    // Add log (file ?)


    virtual void nextPlayer();


public:
    virtual void play();  // function when a player play. Call Listener.onPlayerPlay




    static Game findAdversary(Player player); // Find a other player to play a game

};




#endif	/* GAME_HPP */

