
#include "Game.hpp"


std::queue<Player*> Game::PlayerWaitGame;


//////////// PRIVATE ////////////


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
    //WizardLogger::info("Création d'une partie opposant " +
    //    _player1->getUsername() + " et " + _player2->getUsername());

}


/**
 * Switches player turn
 */
void Game::nextPlayer() {
    (_currentPlayer == _player1) ? _currentPlayer = _player2 : _currentPlayer = _player1;
    // WizardLogger::info("C'est maintenant au tour de " + _currentPlayer->getUsername());
    // TO DO message de débug

    beginTurn();
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
 * Get the ennemy player (adversary)
 *
 * @return the ennemy player
 */
PlayerInGame* Game::getAdversePlayer() {
    PlayerInGame* res;
    PlayerInGame* player = this->_currentPlayer;

    (player == _player1) ? res = _player2 : res = _player1;
    // If not player1 or player2 then return null :/

    return res;
}


/**
 * Gets the ennemy placed card
 *
 * @param player the current player
 */
std::vector<CardMonster*> Game::getAdversePlacedCard(PlayerInGame* player) {
    return getAdversePlayer(player)->getCardsPlaced();
}



//////////// PUBLIC ////////////


/**
 * Default constructor
 */
Game::Game(): _gameStatut(GameStatut::WAIT_DEC),
    _currentPlayer(nullptr), _turn(0),
    _player1(nullptr), _player2(nullptr) {}


/**
 * Copy constructor
 *
 * @param game who must be copied
 */
Game::Game(const Game& game): _gameStatut(game._gameStatut),
    _currentPlayer(game._currentPlayer), _player1(game._player1),
    _player2(game._player2) {}


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
 * Checks if the player have set his deck
 * If all is ok, the game starts
 */
void Game::checkDeckAndStart() {
    if(_player1->isDeckDefined() && _player2->isDeckDefined()) {
        sendInformation();
    }
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
     //   new Game(p1, &player); // creates game

    } else {
        PlayerWaitGame.push(&player); // adds player to the waiting list
    }
}


/**
 * Current player draw a card
 */
void Game::draw() {
    _currentPlayer->draw();
}


/**
 * Function when player place card. This function place the card
 * and verify that all is ok
 *
 * @param pIG who make the action
 * @param placeCard which is place
 * @return Error or "NoError" if all is ok
 */
Error Game::placeCard(PlayerInGame* pIG, Card* placeCard) {
    Error res = Error::UnknowError;

    if(pIG == _currentPlayer) {
        if(!placeCard->isMonster() || havePlace(pIG)) {
            if(pIG->haveEnoughEnergy(placeCard)) {
                if(placeCard->isMonster()) {
                    pIG->placeCard(dynamic_cast<CardMonster*>(placeCard));
                }
                res = Error::NoError;

            } else {
                res = Error::NotEnoughEnergy;
            }
        } else {
            res = Error::NotEnoughPlace;
        }
    } else {
        res = Error::NotHisTurn;
    }

    return res;
}


/**
 * Function when player place card
 *
 * @param pIG player who place the card
 * @param cardPlaced the card the must be place
 * @param targetCard the card which will have the effect if
 * the placed card have it
 */
Error Game::placeCard(PlayerInGame* pIG, Card* cardPlaced,
    CardMonster* targetCard) {

    Error res = placeCard(pIG, cardPlaced);

    if(res == Error::NoError) {
        // Verify effect and play it
        // TO DO
        // cardPlaced->applyEffect(*targetCard);
    }

    return res;
}


/**
 * Funciton when player attack a card
 * @param pIG who play
 * @param card which play
 * @param targetCard card which is attack
 * @return Error or "NoError" if all is ok
 */
Error Game::attackWithCard(PlayerInGame* pIG, CardMonster* card,
    CardMonster* targetCard) {


    Error res = canPlayerAttack(pIG, card);
    if(res == Error::NoError) {
        if(verifyTaunt(pIG, card)) {
            card->dealDamage(*targetCard);
            if(targetCard->isDeath()) {
                this->getAdversePlayer()->defausseCardPlaced(targetCard);
            }
        } else {
            res = Error::MustAttackTaunt;
        }
    }

    return res;
}

/**
 * Funciton when player attack a card

 * @param pIG who play
 * @param card which play
 * @param targetCard card which is attack
 * @return Error or "NoError" if all is ok
 */
Error Game::attackWithCard(PlayerInGame* pIG, CardMonster* card,
    PlayerInGame* targetCard) {

    // TO DO
}

//////////// PRIVATE ////////////

/**
 * Function when the turn begin
 */
void Game::beginTurn() {
    // Increment number of turn
    vector<CardMonster*> cardPlaced = _currentPlayer->getCardsPlaced();
    for (size_t i = 0; i < cardPlaced.size(); ++i) {
        cardPlaced[i]->incrementTour();
    }


    while(_currentPlayer->nbrCardInHand() < 7) {
        draw();
    }


}


/**
 * Function when the turn is finish
 */
void Game::endTurn() {

    while(_currentPlayer->nbrCardInHand() > 7) {
        // askDefausse(...
        // @tutul
    }

}


/**
 * Verify that player can play
 * /!\ Error send to advert client if not valide
 *
 * @param pIG player that play
 * @param card card that is play
 * @return the Error or "NoError"
 */
Error Game::canPlayerAttack(PlayerInGame* pIG, CardMonster* card) {
    Error res = Error::UnknowError;

    if(pIG == _currentPlayer) {
        if(card->getNbrTourPose() > 1) {
            if(pIG->haveEnoughEnergy(card)) {
                res = Error::NoError;
            } else {
                res = Error::NotEnoughEnergy;
            }
        } else {
             Error::NotEnoughPlace;
        }
    } else {
        Error::NotHisTurn;
    }

    return res;
}


/**
 * Verify that the player havn't an taunt effect
 *
 * @param pIG player the must be verified
 * @param card that is attack
 * @return True if all is ok, False if a card is taunt
 * and isn't the card that we attack
 */
bool Game::verifyTaunt(PlayerInGame* pIG, CardMonster *card) {
    return card->isTaunt() || verifyTaunt(pIG);
}


/**
 * Verify that the player havn't an taunt effect
 *
 * @param pIG player the must be verified
 * @return True if all is ok, False if a card is taunt
 */
bool Game::verifyTaunt(PlayerInGame* pIG) {
    bool res = true;

    vector<CardMonster*> cardPlaced = pIG->getCardsPlaced();
    size_t i = 0;
    while(i < cardPlaced.size() && res) {
        res = !(cardPlaced[i]->isTaunt());
        ++i;
    }

    return res;
}


/**
 * Indicate whether the still has place on his game board
 *
 * @param pIG where we must make verification
 * @return True if the have place
 */
bool Game::havePlace(PlayerInGame* pIG) {
    return _currentPlayer->getCardsPlaced().size() < 7;
}


/**
 * Function when player place card
 *
 * @param pIG player who place the card
 * @param cardPlaced the card the must be place
 * @param targetPlayer player who will have the effect if
 * the placed card have it
 * @return Error or "NoError" if all ok
 */
Error Game::placeCard(PlayerInGame* pIG, Card* cardPlaced,
    PlayerInGame* targetPlayer) {

    Error res = placeCard(pIG, cardPlaced);


    if(res == Error::NoError) {
        // Verify if card have effect and apply it
        // TO DO
        // Regarder que la carte peut attaquer le player
        // cardPlaced->applyEffect(*targetPlayer);
    }

    return res;
}


Error Game::attackWithCard(PlayerInGame* pIG,CardMonster* card) {
// TO DO
}
