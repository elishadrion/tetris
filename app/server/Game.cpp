
#include "Game.hpp"


std::vector<Player*> Game::PlayerWaitGame;


//////////// PRIVATE ////////////

// les fonctions de PacketManager ont toutes besoins de Player* en premier argument
//     il s'agit du joueur à qui envoyer le message, vu que c'est Player qui contient le socket


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
    _turn = 0;
    _gameStatut = GameStatut::WAIT_DEC;
    WizardLogger::info("Création d'une partie opposant " +
        _player1->getName() + " et " + _player2->getName());

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
    return getAdversePlayer(_currentPlayer);
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
    _currentPlayer(game._currentPlayer), _turn(game._turn),
    _player1(game._player1), _player2(game._player2) {

    std::string msg = "Copie d'une partie. Attention à ne pas oublier de ";
    msg += "supprimer la précédente. Perte de mémoire potentiel";
    WizardLogger::warning(msg);
}


/**
 * Checks if the player have set his deck
 * If all is ok, the game starts
 */
void Game::checkDeckAndStart() {
    if(_player1->isDeckDefined() && _player2->isDeckDefined()) {

        _gameStatut = GameStatut::IN_GAME;
        PacketManager::initGame(_player1, getAdversePlayer(_player1)->getName());
        PacketManager::initGame(_player2, getAdversePlayer(_player2)->getName());

        unsigned int i = 0;
        while(i < 5) {
            _player1->draw();
            _player2->draw();
            ++i;
        }

        nextPlayer();

        /*
            send CardInHand
             => sendStartTurnInfo(Player*, dataIGPlayer, std::std::vector<CardMonster*>, int, int, int)
             with current player info, ennemy placed card, ennemy card in hand, ennemy card in deck
                (and ennemy card in trash ?)
                [you must send both packet, the first start the game and the second start the player turn
                 OR we add ataIGPlayer in the initGame, you choose]

            https://thegithubbers.slack.com/archives/communication/p1456306333000004
            TO DO @tutul
        */

    }
}


/**
 * Adds a player to the waiting list
 * If there is more than one player who is waiting, then it creates a Game
 * {STATIC}
 *
 * @param player the new player waiting
 */
void Game::addPlayerWaitGame(Player *player) {
    if(!PlayerWaitGame.empty()) {
        // Si on a trouvé le joueur dans la liste
        if(std::find(PlayerWaitGame.begin(), PlayerWaitGame.end(), player) != PlayerWaitGame.end()) {
            WizardLogger::info(player->getName() + " attend déjà");
        } else {

            Player* p1 = PlayerWaitGame.back(); // gets last player
            PlayerWaitGame.pop_back();
            new Game(p1, player); // creates game
        }

    } else {
        PlayerWaitGame.insert(PlayerWaitGame.begin(), player); // adds player to the waiting list
        WizardLogger::info(player->getName() + " attend une partie");
    }
}

/**
 * Remove a player from the waiting list
 * {STATIC}
 *
 * @param player the player to remove
 */
void Game::removePlayerWaitGame(Player *player) {
    std::vector<Player*>::iterator it = std::find(PlayerWaitGame.begin(), PlayerWaitGame.end(), player);
    if(it != PlayerWaitGame.end()) {
        PlayerWaitGame.erase(
            std::remove(PlayerWaitGame.begin(), PlayerWaitGame.end(), player),
            PlayerWaitGame.end());
            WizardLogger::info(player->getName() + " n'attend plus de partie");
    }
}


/**
 * Current player draw a card
 */
void Game::draw() {
    draw(_currentPlayer);
}


/**
 * Specific player draw a card
 *
 * @param pIG who must draw
 */
void Game::draw(PlayerInGame* pIG) {
    Card* res = pIG->draw();
    if(res == nullptr) { // If no card
        pIG->takeDamage(4);
        isPlayerInLife();

        PacketManager::playerDamage(_player1, pIG->getName(), pIG->getHeal());
        PacketManager::playerDamage(_player2, pIG->getName(), pIG->getHeal());

    } else {
        PacketManager::sendCard(pIG, res);
    }

}


/**
 * Function when player place card and attack player
 *
 * @param pIG player who place the card
 * @param cardPlaced the card the must be place
 * @param targetPlayer player who will have the effect if
 * the placed card have it
 * @return Error or "NoError" if all ok
 */
Error Game::placeCardAffectPlayer(PlayerInGame* pIG, Card* cardPlaced) {

    Error res = canPlaceCard(pIG, cardPlaced);

    if(res == Error::NoError && cardPlaced->gotEffect()) {
        if(cardPlaced->canBeApplyOnPlayer()) {
            PlayerInGame* pAdverse = getAdversePlayer(pIG);
            cardPlaced->applyEffect(*pAdverse, *this);
            // Send information to clients
            sendInfoAction(pIG->getName(), cardPlaced->getId(), -1, pAdverse->getHeal(),
                           true, !cardPlaced->isMonster());
            isPlayerInLife(pAdverse); // Is player in life ?
        } else {
            res = Error::NotEffectForPlayer;
        }
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
Error Game::placeCard(PlayerInGame* pIG, CardMonster* cardPlaced) {

    Error res = canPlaceCard(pIG, cardPlaced);

    if(res == Error::NoError) {
        int position = getRealPosition(pIG, pIG->placeCard(cardPlaced));
        //PacketManager::sendPlaceMonsterCard(_player1, pIG->getName(), cardPlaced->getId(), position);

        // Send information to clients
        //sendInfoAction(pIG->getName(), cardPlaced->getId(), targetCard->getId(), targetCard->getLife(),
        //               true, !cardPlaced->isMonster());
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

    Error res = canPlaceCard(pIG, cardPlaced);

    if(res == Error::NoError) {
        // Verify if effect can be apply on monster
        cardPlaced->applyEffect(*targetCard, *this);

        // Send information to clients
        sendInfoAction(pIG->getName(), cardPlaced->getId(), targetCard->getId(), targetCard->getLife(),
                       true, !cardPlaced->isMonster());
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
Error Game::attackWithCard(PlayerInGame* pIG, unsigned cardPosition,
    unsigned targetPosition) {

    PlayerInGame* adverse = getAdversePlayer(pIG);

    CardMonster* card = pIG->getCardAtPosition(getRelativePosition(pIG, cardPosition));
    CardMonster* targetCard = adverse->getCardAtPosition(getRelativePosition(adverse, targetPosition));

    Error res = canPlayerAttack(pIG, card);
    if(res == Error::NoError) {
        if(verifyTaunt(pIG, targetCard)) {
            card->dealDamage(*targetCard);
            if(targetCard->isDead()) {
                this->getAdversePlayer()->defausseCardPlaced(targetPosition);
            }

//            sendInfoAction(pIG->getName(), card->getId(), targetCard->getId(), targetCard->getLife(),
//                           false, false);
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
Error Game::attackWithCardAffectPlayer(PlayerInGame* pIG, unsigned cardPosition) {

    CardMonster* card = pIG->getCardAtPosition(getRelativePosition(pIG, cardPosition));

    Error res = canPlayerAttack(pIG, card);
    if(res == Error::NoError) {
        if(verifyTaunt(pIG)) {
            PlayerInGame* pAdverse = getAdversePlayer(pIG);
            card->dealDamage(*pAdverse);

            //sendInfoAction(pIG->getName(), card->getId(), -1, pAdverse->getHeal(), false, false);
            isPlayerInLife(pAdverse);
        } else {
            res = Error::MustAttackTaunt;
        }
    }

    return res;
}


/**
 * Switches player turn
 */
void Game::nextPlayer() {
    (_currentPlayer == _player1) ? _currentPlayer = _player2 : _currentPlayer = _player1;
    WizardLogger::info("C'est maintenant au tour de " + _currentPlayer->getName());

    if(_currentPlayer == _player1) {
        ++_turn;
    }
    _currentPlayer->addMaxEnergy();
    _currentPlayer->resetEnergy();

    PacketManager::sendTurnInfo(_player1, _player2, _currentPlayer==_player1);
    PacketManager::sendTurnInfo(_player2, _player1, _currentPlayer==_player2);

    beginTurn();
}


/**
 * Send information
 *
 * @param pIG who play
 * @param cardID
 * @param targetCard card which is attack (-1 if player)
 * @param heal of the attack entity
 * @param isEffect is the attack an effect
 * @param newCard is the card new on the board
 * @param isCardEffect the card who attack is a card effect
 */
void Game::sendInfoAction(std::string pseudo, int cardID, int targetCard, unsigned heal,
    bool newCard, bool isCardEffect) {

//    if(!newCard) {
//        PacketManager::sendAttack(_player1, pseudo, cardID, targetCard, heal);
//        PacketManager::sendAttack(_player2, pseudo, cardID, targetCard, heal);
//    } else {
//        if(isCardEffect) {
//            PacketManager::sendPlaceSpellCard(_player1, pseudo, cardID, targetCard, heal);
//            PacketManager::sendPlaceSpellCard(_player2, pseudo, cardID, targetCard, heal);
//        } else {
//            PacketManager::sendPlaceMonsterCard(_player1, pseudo, cardID, targetCard, heal);
//            PacketManager::sendPlaceMonsterCard(_player2, pseudo, cardID, targetCard, heal);
//        }
//    }
}


//////////// PRIVATE ////////////

/**
 * Function when the turn begin
 */
void Game::beginTurn() {
    // Increment number of turn
    _currentPlayer->incrementAllPlaceCard();

    while(_currentPlayer->nbrCardInHand() < 5) {
        draw();
    }

}


/**
 * Function when the turn is finish
 */
void Game::endTurn() {

    int nbrCard = MAX_HAND-_currentPlayer->nbrCardInHand();
    if(nbrCard < 0) {
        PacketManager::askDefausse(_currentPlayer, -nbrCard);
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
             res = Error::NotEnoughPlace;
        }
    } else {
        res = Error::NotHisTurn;
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
    return pIG->haveOneCardTaunt();
}


/**
 * Indicate whether the still has place on his game board
 *
 * @param pIG where we must make verification
 * @return True if the have place
 */
bool Game::havePlace(PlayerInGame* pIG) {
    return pIG->havePlace();
}


/**
 * Check if the current player is in life and if he is dead,
 * tell it and delete Game
 */
void Game::isPlayerInLife() {
    isPlayerInLife(_currentPlayer);
}



/**
 * Check if player is in life and if he is dead, tell it and
 * delete Game
 *
 * @param pIG player to check
 */
void Game::isPlayerInLife(PlayerInGame* pIG) {
    if(pIG->isDead()) {
        PlayerInGame* pAdverse = getAdversePlayer(pIG);

        pIG->addDefeat();
        pAdverse->addWin();


        bool p1Win = (_player1 == pAdverse);
        int winCard = CardManager::chooseCardWin()->getId();

        PacketManager::sendEndGame(_player1, p1Win ? 1 : -1, p1Win ? winCard : -1);
        PacketManager::sendEndGame(_player2, (!p1Win) ? 1 : -1, (!p1Win) ? winCard : -1);

        delete this;
    }
}


/**
 * Calcul the real position of a card on the board (if player 2 make + MAX_POSED_CARD)
 *
 * @param pIG playerInGame who have this relative position
 * @param initPosition relative position of the player
 * @return the real position
 */
int Game::getRealPosition(PlayerInGame* pIG, int initPosition) {
    int res = initPosition;
    if(pIG == _player2) {
        res += MAX_POSED_CARD;
    }

    return res;
}

/**
 * Calcul the relative position of a card for this player (if player 2 make - MAX_POSED_CARD)
 *
 * @param pIG playerInGame who we would like the relative position
 * @param initPosition real position of the card on the board
 * @return the relative position
 */
int Game::getRelativePosition(PlayerInGame* pIG, int initPosition) {
    int res = initPosition;
    if(pIG == _player2) {
        if(initPosition < MAX_POSED_CARD) {
            WizardLogger::error("Le calcul relatif de la carte est erroné");
        }
        res -= MAX_POSED_CARD;
    }

    return res;
}



/**
 * Function when player place card. This function place the card
 * and verify that all is ok
 *
 * @param pIG who make the action
 * @param placeCard which is place
 * @return Error or "NoError" if all is ok
 */
Error Game::canPlaceCard(PlayerInGame* pIG, Card* placeCard) {
    Error res = Error::UnknowError;

    if(pIG == _currentPlayer) {
        if(!placeCard->isMonster() || havePlace(pIG)) {
            if(pIG->haveEnoughEnergy(placeCard)) {
//                if(placeCard->isMonster()) {
//                    pIG->placeCard(dynamic_cast<CardMonster*>(placeCard));
//                }
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
 * Call when a party end becase a player disconnect
 *
 * @param pIG who disconnect
 */
void Game::endParty(PlayerInGame* pIG) {
    PacketManager::sendEndGame(getAdversePlayer(pIG), 0, -1);
    delete this;
}


/**
 * Destructor
 */
Game::~Game() {
    _player1->removePlayerInGame(_player1);
    _player2->removePlayerInGame(_player2);
    delete _player1;
    delete _player2;
}
