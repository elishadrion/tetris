
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
 * Current player draw a card
 */
void Game::draw() {
    draw(_currentPlayer);
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

    Error res = placeCard(pIG, cardPlaced);

    if(res == Error::NoError && cardPlaced->gotEffect()) {
        if(cardPlaced->canBeApplyOnPlayer()) {
            PlayerInGame* pAdverse = getAdversePlayer(pIG);
            cardPlaced->applyEffect(*pAdverse, *this);
            // Send information to clients
            sendInfoAction(pIG, cardPlaced->getId(), -1, true, true, pAdverse->getHeal());
            isPlayerInLife(pAdverse); // Is player inlife ?
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
Error Game::placeCard(PlayerInGame* pIG, Card* cardPlaced,
    CardMonster* targetCard) {

    Error res = placeCard(pIG, cardPlaced);

    if(res == Error::NoError) {
        // Verify if effect can be apply on monster
        cardPlaced->applyEffect(*targetCard, *this);

        // Send information to clients
        sendInfoAction(pIG, cardPlaced->getId(), targetCard->getId(), true, true, targetCard->getLife());
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
        if(verifyTaunt(pIG, targetCard)) {
            card->dealDamage(*targetCard);
            if(targetCard->isDead()) {
                this->getAdversePlayer()->defausseCardPlaced(targetCard);
            }

            sendInfoAction(pIG, card->getId(), targetCard->getId(), false, false, targetCard->getLife());
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
Error Game::attackWithCardAffectPlayer(PlayerInGame* pIG,
    CardMonster* card) {

    Error res = canPlayerAttack(pIG, card);
    if(res == Error::NoError) {
        if(verifyTaunt(pIG)) {
            PlayerInGame* pAdverse = getAdversePlayer(pIG);
            card->dealDamage(*pAdverse);

            sendInfoAction(pIG, card->getId(), -1, false, false, pAdverse->getHeal());
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
 * @param cardWichAttack
 * @param attackCard card which is attack (-1 if player)
 * @param isEffect is the attack an effect
 * @param newCard is the card new on the board
 * @param heal of the attack entity
 */
void Game::sendInfoAction(PlayerInGame* pIG, int cardWichAttack, int attackCard,
    bool isEffect, bool newCard, unsigned heal) {//TODO can't send all like these, seperate attack and spell

    PacketManager::sendAttack(_player1, pIG->getName(), attackCard, cardWichAttack, heal, isEffect, newCard);
    PacketManager::sendAttack(_player2, pIG->getName(), attackCard, cardWichAttack, heal, isEffect, newCard);
}


//////////// PRIVATE ////////////

/**
 * Function when the turn begin
 */
void Game::beginTurn() {
    // Increment number of turn
    std::vector<CardMonster*> cardPlaced = _currentPlayer->getCardsPlaced();
    for (size_t i = 0; i < cardPlaced.size(); ++i) {
        cardPlaced[i]->incrementTour();
    }


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

/*
 * Function when the game is init to
 * send information to all players
 *
void Game::sendInitInfo() {
    sendInitInfo(_player1);
    sendInitInfo(_player2);
}


/*
 * Function when the game is init to
 * send informtaions to the player
 *
 * @param pIG to send message
 *
void Game::sendInitInfo(PlayerInGame* pIG) {
    pIG->getCardsInHand(); // CardsInHand
    pIG == _currentPlayer; // His turn ?
    getAdversePlayer(pIG); // Adverse player


    // TO DO @tutul
    // Send initGame (see upper) + setTurn (see upper) + sendStartTurnInfo (see upper)
    // No ???
}
*/

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
    bool res = true;

    std::vector<CardMonster*> cardPlaced = pIG->getCardsPlaced();
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
    return pIG->getCardsPlaced().size() < MAX_POSED_CARD;
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

        PacketManager::sendEndGame(_player1, _player1==pAdverse ? 1 : -1, -1);//TODO replace -1 by card's ID
        PacketManager::sendEndGame(_player2, _player2==pAdverse ? 1 : -1, -1);//TODO replace -1 by card's ID


        Card* card = CardManager::chooseCardWin();
        //pAdverse->addCardCollection(card); wait Carlos
        // TO DO @tutul
        // send cardWin ?


        delete this;
    }
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
 * Call when a party end becase a player disconnect
 *
 * @param pIG who disconnect
 */
void Game::endParty(PlayerInGame* pIG) {
    PacketManager::sendEndGame(getAdversePlayer(pIG), 0, -1);
    delete _player1;
    delete _player2;
    delete this;
}
