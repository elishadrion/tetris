
#include "Game.hpp"



/**
 * Switch turn player
 */
void Game::nextPlayer() {
    currentPlayer = (currentPlayer+1)%2;
}

/**
 * Find a game for the player.  This function create the game or
 */
void Game::findAdversary(Player player) {
    if(PlayerWaitGame.size() > 1) {
        Player* p1 = PlayerWaitGame[0];
        PlayerWaitGame.erase(PlayerWaitGame.begin());
    }
}

