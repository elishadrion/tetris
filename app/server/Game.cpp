
#include "Game.hpp"


std::queue<Player*> Game::PlayerWaitGame;


/**
 * Switches player turn
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
Game::Game(Player* p1, Player* p2):
    _gameStatut(GameStatut::WAIT_DEC), _turn(0) {

    // Constructor asks player which deck he would like
    _player1 = new PlayerInGame(*p1, this);
    _player2 = new PlayerInGame(*p2, this);
    _currentPlayer = _player1;
}

/**
 * Copy constructor
 *
 * @param game who must be copied
 */
Game::Game(const Game& game): _gameStatut(game._gameStatut),
    _currentPlayer(game._currentPlayer), _player1(game._player1),
    _player2(game._player2) {}

/**
 * Default constructor
 */
Game::Game(): _gameStatut(GameStatut::WAIT_DEC),
    _currentPlayer(nullptr), _turn(0),
    _player1(nullptr), _player2(nullptr) {}


/**
 * Copy operator
 */
Game& Game::operator=(const Game& game) {
    _currentPlayer = game._currentPlayer;
    _player1 = game._player1;
    _player2 = game._player2;
    _gameStatut = game._gameStatut;

    return *this;
}



/**
 * Adds a player to the waiting list
 * If there is more than one player who is waiting, then it creates a Game
 *
 * @param player the new player waiting
 */
void Game::addPlayerWaitGame(Player player) {
    if(!PlayerWaitGame.empty()) {
        Player* p1 = PlayerWaitGame.front(); // gets first player
        PlayerWaitGame.pop(); // removes first player
        new Game(p1, &player); // creates game

    } else {
        PlayerWaitGame.push(&player); // adds player to the waiting list
    }
}

/**
 * Checks if the player have set his deck
 * If all is ok, the game starts
 */
void Game::checkDeckAndStart() {
    if(_player1->isDeckDefine() && _player2->isDeckDefine()) {
        sendInformation();
    }
}

/**
 * Know if the game has begun
 *
 * @return True if the game has begun
 */
bool Game::isInGame() {
    return _gameStatut == GameStatut::IN_GAME;
}


/**
 * Sends information about the game to all players
 */
void Game::sendInformation() {

    dataIGPlayer dataPlayer1 = _player1->getDataPlayer();
    dataIGPlayer dataPlayer2 = _player2->getDataPlayer();

    sendInformation(_player1, dataPlayer1, dataPlayer2);
    sendInformation(_player2, dataPlayer2, dataPlayer1);
}


/**
 * Gets the ennemy placed card
 *
 * @param player the current player
 */
std::vector<Card*> Game::getAdversePlacedCard(PlayerInGame* player) {
    return getAdversePlayer(player)->getCardPlaced();
}

/**
 * Get the ennemy player (adversary)
 *
 * @param player current player
 * @return the ennemy player
 */
PlayerInGame* Game::getAdversePlayer(PlayerInGame* player) {
    PlayerInGame* res;

    (player == _player1) ? res = _player2 : res = _player1;
    // If not player1 or player2 then returns null :/

    return res;
}

/**
 * Sends information about the game
 *
 * @param player who receive the information
 */
void Game::sendInformation(PlayerInGame* player,
    dataIGPlayer dataPlayer, dataIGPlayer dataAdvPlayer) {

    // init turn
    dataPlayer.turn = (player == _currentPlayer);
    dataAdvPlayer.turn = (player != _currentPlayer); // can be remove ?(=?)

    dataAdvPlayer.cardsInHand.clear();

    // sends information to the player (dataPlayer and dataAdvPlayer)
    // @tutul
}

void Game::draw() {
    // TO DO

}


