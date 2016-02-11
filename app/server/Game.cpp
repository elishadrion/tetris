
#include "Game.hpp"


std::queue<Player*> Game::PlayerWaitGame;


/**
 * Switch turn player
 */
void Game::nextPlayer() {
    (_currentPlayer == _player1) ? _currentPlayer = _player2 : _currentPlayer = _player1;
}


/**
 * Game constructor
 *
 * @param p1 the first player
 * @param p2 the second player
 */
Game::Game(Player* p1, Player* p2): _turn(0) {

    // Constructeur ask player whitch deck he would like
    _player1 = new PlayerInGame(*p1, this);
    _player2 = new PlayerInGame(*p2, this);
    _currentPlayer = _player1;
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
Game::Game(): _currentPlayer(nullptr), _turn(0),
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
 * Check if the player have set he deck
 * If all is ok, the game start
 */
void Game::checkDeckAndStart() {
    if(_player1->isDeckDefine() && _player2->isDeckDefine()) {
        sendInformation();
    }
}


/**
 * Send information about the game to all player
 */
void Game::sendInformation() {

    dataIGPlayer dataPlayer1 = _player1->getDataPlayer();
    dataIGPlayer dataPlayer2 = _player2->getDataPlayer();

    sendInformation(_player1, dataPlayer1, dataPlayer2);
    sendInformation(_player2, dataPlayer2, dataPlayer1);
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

    (player == _player1) ? res = _player2 : res = _player1;
    // If not player1 or player2 then return null :/

    return res;
}

/**
 * Send information about the game
 *
 * @param player who recieve the information
 */
void Game::sendInformation(PlayerInGame* player,
    dataIGPlayer dataPlayer, dataIGPlayer dataAdvPlayer) {

    // init turn
    dataPlayer.turn = (player == _currentPlayer);
    dataAdvPlayer.turn = (player != _currentPlayer); // can be remove ?

    dataAdvPlayer.cardsInHand.clear();

    // send information to the player
    // @tutul
}


