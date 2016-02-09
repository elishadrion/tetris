
#include "Game.hpp"



/**
 * Switch turn player
 */
void Game::nextPlayer() {
    _currentPlayer = (_currentPlayer+1)%2;
}


/**
 * Game constructor
 *
 * @param p1 the first player
 * @param p2 the second player
 */
Game::Game(Player* p1, Player* p2): _currentPlayer(0) { // currentPlayer automatic init ?
    //_player1 = new PlayerInGame(p1);
    //_player2 = new PlayerInGame(p2);

}


/**
 * Add a player to the wait list
 * If there is more than one player who waits, then create a Game
 *
 * @param player the new player waiting
 */
void Game::addPlayerWaitGame(Player player) {
    if(PlayerWaitGame.size() > 1) {
        Player* p1 = PlayerWaitGame[0];
        PlayerWaitGame.erase(PlayerWaitGame.begin());
        new Game(p1, &player);
    } else {
        PlayerWaitGame.push_back(&player);
    }
}

