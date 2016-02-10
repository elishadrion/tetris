
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
Game::Game(Player* p1, Player* p2): _currentPlayer(0),
    _turn(0) {

    _player1 = new PlayerInGame(*p1);
    _player2 = new PlayerInGame(*p2);


}

/**
 * Copy constructor
 *
 * @param game who muste be copy
 */
Game::Game(const Game& game): _currentPlayer(game._currentPlayer),
    _player1(game._player1), _player2(game._player2) {}

/**
 * Default constructor
 */
Game::Game(): _currentPlayer(0), _turn(0),
    _player1(nullptr), _player2(nullptr) {}


/**
 * Copy operrator
 */
Game& Game::operator=(const Game& game) {
    _currentPlayer = game._currentPlayer;
    _player1 = game._player1;
    _player2 = game._player2;

    return *this;
}



/**
 * Add a player to the wait list
 * If there is more than one player who waits, then create a Game
 *
 * @param player the new player waiting
 */
void Game::addPlayerWaitGame(Player player) {
    if(!PlayerWaitGame.empty()) {
        Player* p1 = PlayerWaitGame.front(); // get first player
        PlayerWaitGame.pop(); // remove first player
        new Game(p1, &player); // create game


    } else {
        PlayerWaitGame.push(&player); // add to the wait list
    }
}

/**
 * Send information about the game to all player
 */
void Game::sendInformation() {
    sendInformation(_player1);
    sendInformation(_player2);
}


/**
 * Get the adverse placed card
 *
 * @param player the current player
 */
std::vector<Card*> Game::getAdversePlacedCard(PlayerInGame* player) {
    return getAdversePlayer(player)->getCardPlaced();
}

/**
 * Get the adverse player
 *
 * @param player current player
 * @return the adverse player
 */
PlayerInGame* Game::getAdversePlayer(PlayerInGame* player) {
    PlayerInGame* res;

    if(player == _player1) {
        res = _player2;
    } else if(player == _player2) {
        res = _player1;
    }
    // If not player1 or player2 then return null :/

    return res;
}

/**
 * Send information about the game
 *
 * @param player who recieve the information
 */
void Game::sendInformation(PlayerInGame* player) {
    player->sendData(_currentPlayer, _turn, getAdversePlacedCard(player));
}




