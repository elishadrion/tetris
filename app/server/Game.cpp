
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

    // Ask to the players his deck
    PacketManager::askDeck(_player1, _player2->getName());
    PacketManager::askDeck(_player2, _player1->getName());

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

        unsigned int i = 0;
        std::vector<unsigned> handPlayer1;
        std::vector<unsigned> handPlayer2;
        while(i < MIN_CARD_IN_HAND) {
            handPlayer1.push_back(_player1->draw()->getId());
            handPlayer2.push_back(_player2->draw()->getId());
            ++i;
        }
        PacketManager::sendDrawBegin(_player1, handPlayer1);
        PacketManager::sendDrawBegin(_player2, handPlayer2);

        usleep(100);
        nextPlayer();
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
    WizardLogger::info("Game: draw: " + res->getName());
    if(res == nullptr) { // If no card
        pIG->takeDamage(4);

        PacketManager::playerDamage(_player1, pIG->getName(), pIG->getHeal());
        PacketManager::playerDamage(_player2, pIG->getName(), pIG->getHeal());
        isPlayerInLife();

    } else {
        PacketManager::sendCard(pIG, res);
        PacketManager::sendAdverseDraw(getAdversePlayer(pIG));
    }

}


/**
 * Function when player place card
 *
 * @param pIG player who place the card
 * @param cardPlaced the card the must be place
 */
Error Game::placeCard(PlayerInGame* pIG, CardMonster* cardPlaced) {

    Error res = canPlaceCard(pIG, cardPlaced);

    if(res == Error::NoError) {
        int relPosition = pIG->placeCard(cardPlaced);
        if(relPosition == -1) {
            res = Error::NotEnoughPlace;
        } else {
            int position = getRealPosition(pIG, relPosition);
            std::string pseudo = pIG->getName();
            int idCard = cardPlaced->getId();

            PacketManager::sendPlaceMonsterCard(_player1, pseudo, idCard, position);
            PacketManager::sendPlaceMonsterCard(_player2, pseudo, idCard, position);
        }

    }

    return res;
}


/**
 * Function when player place card and attack an other
 *
 * @param pIG player who place the card
 * @param cardPlaced the card the must be place
 * @param targetCard the card which will have the effect if
 * the placed card have it
 */
Error Game::placeCardAffect(PlayerInGame* pIG, Card* cardPlaced, unsigned targetPosition) {
    Error res = canPlaceCard(pIG, cardPlaced);

    if(res == Error::NoError) {

        if(targetPosition == -1 && (!cardPlaced->gotEffect() || !cardPlaced->canBeApplyOnPlayer())) {
            res = Error::NotEffectForPlayer;

        } else if(!cardPlaced->gotEffect() || !cardPlaced->canBeApplyOnCard()) {
            res = Error::NotEffectForMonster;

        } else {

            PlayerInGame* adverse = getAdversePlayer(pIG);
            unsigned lifeTarget;

            // If it's a card the is attack
            if(targetPosition != -1) {
                // Get the target Card
                CardMonster* targetCard = getCardAtPosition(targetPosition);

                // Apply effect
                cardPlaced->applyEffect(*targetCard, *this);
                lifeTarget = targetCard->getLife(); // save heal

            } else { // If we attack the adverse player

                cardPlaced->applyEffect(*adverse, *this);
                lifeTarget = adverse->getHeal(); // save heal
            }



            // Send information to clients
            std::string pseudo = pIG->getName();
            int placedCardId = cardPlaced->getId();

            if(cardPlaced->isMonster()) {
                // Get the position of the new card
                int positionNewCard = getRealPosition(pIG,
                                                 pIG->placeCard(static_cast<CardMonster*>(cardPlaced)));

                PacketManager::sendPlaceMonsterCard(_player1, pseudo, placedCardId, positionNewCard,
                                                    targetPosition, lifeTarget);
                PacketManager::sendPlaceMonsterCard(_player2, pseudo, placedCardId, positionNewCard,
                                                    targetPosition, lifeTarget);

            } else {
                pIG->defausseCardInHand(cardPlaced);
                PacketManager::sendPlaceSpellCard(_player1, pseudo, placedCardId, targetPosition, lifeTarget);
                PacketManager::sendPlaceSpellCard(_player2, pseudo, placedCardId, targetPosition, lifeTarget);

            }


            // Verify that the player is death or not
            if(targetPosition == -1) {
                isPlayerInLife(adverse);
            }

        }
    }

    return res;
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
    return placeCardAffect(pIG, cardPlaced, -1);
}



/**
 * Funciton when player attack a card
 *
 * @param pIG who play
 * @param card which play
 * @param targetCard card which is attack
 * @return Error or "NoError" if all is ok
 */
Error Game::attackWithCard(PlayerInGame* pIG, unsigned cardPosition,
    unsigned targetPosition) {

    CardMonster* card = getCardAtPosition(cardPosition);
    CardMonster* targetCard = getCardAtPosition(targetPosition);

    Error res = canPlayerAttack(pIG, card);
    if(res == Error::NoError) {
        if(verifyTaunt(pIG, targetCard)) {
            card->dealDamage(*targetCard);
            if(targetCard->isDead()) {
                this->getAdversePlayer()->defausseCardPlaced(targetPosition);
            }

            std::string pseudo = pIG->getName();
            unsigned life = targetCard->getLife();
            PacketManager::sendAttack(_player1, pseudo, cardPosition, targetPosition, life);
            PacketManager::sendAttack(_player2, pseudo, cardPosition, targetPosition, life);

        } else {
            res = Error::MustAttackTaunt;
        }
    }

    return res;
}


/**
 * Function when player attack a card

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

            unsigned heal = pAdverse->getHeal();
            std::string pseudo = pIG->getName();
            PacketManager::sendAttack(_player1, pseudo, cardPosition, -1, heal);
            PacketManager::sendAttack(_player2, pseudo, cardPosition, -1, heal);
            isPlayerInLife(pAdverse);
        } else {
            res = Error::MustAttackTaunt;
        }
    }

    return res;
}


/**
 * Call when a player will end his turn
 *
 * @param player who would end his turn
 * @return Error or "NoError" if all is ok
 */
Error Game::playerAskEndTurn(PlayerInGame* player) {
    Error res = Error::NotHisTurn;
    if(player == _currentPlayer) {
        res = Error::NoError;
        nextPlayer();
    }

    return res;
}




//////////// PRIVATE ////////////

/**
 * Function when the turn begin
 */
void Game::beginTurn() {
    WizardLogger::info("Début du tour suivant !");
    // Increment number of turn
    _currentPlayer->incrementAllPlaceCard();

    while(_currentPlayer->nbrCardInHand() < MIN_CARD_IN_HAND) {
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
             res = Error::NOT_FIRST_TURN;
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
 * Switches player turn
 */
void Game::nextPlayer() {
    (_currentPlayer == _player1) ? _currentPlayer = _player2 : _currentPlayer = _player1;
    WizardLogger::info("C'est maintenant au tour de " + _currentPlayer->getName());

    if(_currentPlayer == _player2) {
        ++_turn;
    }
    _currentPlayer->addMaxEnergy();
    _currentPlayer->resetEnergy();

    PacketManager::sendTurnInfo(_player1, _turn, _currentPlayer==_player1);
    PacketManager::sendTurnInfo(_player2, _turn, _currentPlayer==_player2);

    beginTurn();
}


/**
 * Get the card at a specific position
 *
 * @param position of the card
 * @return the card position
 */
CardMonster* Game::getCardAtPosition(unsigned position) {
    CardMonster* cardMonster;
    if(position > MAX_POSED_CARD) {
        cardMonster = _player2->getCardAtPosition(position-MAX_POSED_CARD);
    } else {
        cardMonster = _player1->getCardAtPosition(position);
    }

    return cardMonster;
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
void Game::endGame(PlayerInGame* pIG) {
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
