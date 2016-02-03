/* 
 * File:   Partie.hpp
 * Author: Detobel36
 *
 * Created on 2 février 2016, 20:41
 */

#ifndef GAME_HPP
#define	GAME_HPP

/**
 * One class per game.  Contain the two players and all other informations for 
 * the game
 */
class Game {
    
    Game(Player p1, Player p2);
    
    Player _player1;
    Player _player2;
    Player currentPlayer; // Player the must play now
    // Add log (file ?)
    
    
    virtual void nextPlayer();
    
    
public:
    virtual void play();  // function when a player play. Call Listener.onPlayerPlay
    
    
    
};




#endif	/* GAME_HPP */

