#include "GameManager.hpp"

GameManager* GameManager::_instance;

/**
 * Get the main instance
 *
 * @return the instance of this class
 */
GameManager* GameManager::getInstance() {
    return _instance;
}


/**
 * Constructor
 * @param pseudo of the adverse player
 */
GameManager::GameManager(std::string pseudo): _ennemy(pseudo), _heal(MAX_LIFE),
    _adverseHeal(MAX_LIFE), _energy(0), _adverseEnergy(0), _deckName(""),
    _nbrTurn(0), _isTurn(false) {

    _instance = this;
}


/**
 * Set deck and send information to the server
 *
 * @param deckName the deck name
 */
void GameManager::setDeck(std::string deckName) {
    if(_deckName == "") {
        WizardLogger::info("Envoie du nom du deck: " + deckName);

        _deckName = deckName;
        PacketManager::sendSelectedDeck(_deckName.c_str());
    } else {
        WizardLogger::warning("Le deck à déjà été définit");
    }
}


/**
 * Define information about the game
 *
 * @param nbrTurn number of turn since the begin of the game
 * @param isTurn is the player turn
 */
void GameManager::setTurn(unsigned nbrTurn, bool isTurn) {
    _nbrTurn = nbrTurn;
    _isTurn = isTurn;
    wizardDisplay->changeTurn();
}

/**
 * Call when the server inform that the player draw a card
 *
 * @param idCard of the draw card
 */
void GameManager::drawCard(unsigned idCard) {
    Card* card = CacheManager::getCard(idCard);
    _hand.push_back(card);
    wizardDisplay->drawCard(card);
}



/**
 * Remove a card from the hand of the player
 *
 * @param adverse player or not
 * @param card which must be remove
 */
void GameManager::removeCardFromHand(Card* card) {
    bool fini = false;

    unsigned i = 0;
    unsigned taille = _hand.size();
    Card* elem;
    while(i < taille && !fini) {
        elem = _hand[i];
        if(elem == card) {
            _hand[i] = _hand[taille-1];
            _hand.pop_back();
            fini = true;
        }
        ++i;
    }
}

/**
 * Decreases number of in hand adverse card
 */
void GameManager::removeAdverseCardFromHand() {
    --_adverseHandNumber;
}


/**
 * Call when the player place a card
 *
 * @param isEffectCard or not
 * @param cardID the id of the card
 * @param position position of this card (to identify this)
 */
void GameManager::placeCard(int cardID, unsigned position) {
    Card* card = CacheManager::getCard(cardID);
    removeCardFromHand(card);

    card = new Card(*card); // copy card
    card->setPosition(position);
    _posed[position%MAX_POSED_CARD] = card;
    _energy -= card->getEnergyCost();

    //wizardDisplay->placeCard(card);
}

/**
 * Call when the adverse player place a card
 *
 * @param isEffectCard or not
 * @param cardID the id of the placed card
 * @param position of this card
 */
void GameManager::ennemyPlaceCard(int cardID, unsigned position) {
    Card* defaultCard = CacheManager::getCard(cardID);
    removeAdverseCardFromHand();

    // Copy card
    Card* card = new Card(*defaultCard);
    card->setPosition(position);
    _ennemyPosed[position%MAX_POSED_CARD] = card;
    _adverseEnergy -= card->getEnergyCost();

    wizardDisplay->placeAdverseCard(card);
}

/**
 * Call when the player place card and attack
 *
 * @param cardID the id of the new card
 * @param position of the new card
 * @param targetPosition position of the target card (-1 if adverse player)
 * @param heal of the target card after
 */
void GameManager::placeCardAndAttack(bool isEffectCard, int cardID, unsigned position,
                                     int targetPosition, unsigned heal) {
    Card* defaultCard = CacheManager::getCard(cardID);
    removeCardFromHand(defaultCard);
    Card* card = defaultCard;

    if(!isEffectCard) {
        card = new Card(*defaultCard); // copy card
        card->setPosition(position);
        _posed[position%MAX_POSED_CARD] = card;
    }

    _energy -= card->getEnergyCost();
    if(targetPosition == -1) {
        _adverseHeal = heal;
//        if(isEffectCard) {
//            wizardDisplay->placeSpellPlayer(card);
//        } else {
//            wizardDisplay->placeCardAndAttackPlayer(card);
//        }
    } else {
        Card* enemyCard = static_cast<Card*>(_ennemyPosed[targetPosition%MAX_POSED_CARD]);
        enemyCard->setHP(heal);

        if(enemyCard->isDead()) {
            // TO DO
        }

//        if(isEffectCard) {
//            wizardDisplay->placeSpellCard(card, enemyCard);
//        } else {
//            wizardDisplay->placeCardAndAttack(card, enemyCard);
//            if(enemyCard->isDead()) {
//                // TO DO
//                // DETOBEL36
//            }
//        }
    }

}

/**
 * Call when the adverse player place card an attack
 *
 * @param cardID the id of the new card
 * @param position of the new card
 * @param targetPosition position of the target card (-1 if adverse player)
 * @param heal of the target card after
 */
void GameManager::placeAdverseCardAndAttack(bool isEffectCard, int cardID, unsigned position,
                                            int targetPosition, unsigned heal) {
    Card* defaultCard = CacheManager::getCard(cardID);
    removeAdverseCardFromHand();
    Card* card = defaultCard;

    if(!isEffectCard) {
        card = new Card(*defaultCard); // copy card
        card->setPosition(position);
        _ennemyPosed[position%MAX_POSED_CARD] = card;
    }

    _adverseEnergy -= card->getEnergyCost();

    if(targetPosition == -1) {
        _heal = heal;
        if(isEffectCard) {
            wizardDisplay->placeAdverseSpellPlayer(card);
        } else {
            wizardDisplay->placeAdverseCardAndAttackPlayer(card);
        }
    } else {
        Card* enemyCard = static_cast<Card*>(_posed[targetPosition%MAX_POSED_CARD]);
        enemyCard->setHP(heal);
        if(isEffectCard) {
            wizardDisplay->placeAdverseSpellCard(card, enemyCard);
        } else {
            wizardDisplay->placeAdverseCardAndAttack(card, enemyCard);
        }
        if(enemyCard->isDead()) {
            // TO DO
            // DETOBEL36
        }
    }
}


/**
 * Modify GameManager when the player attack other
 *
 * @param cardPosition the card which attack
 * @param targetPosition the card wich IS attack (-1 for advers player)
 * @param heal the heal of the target card
 */
void GameManager::attackCard(unsigned cardPosition, int targetPosition, unsigned heal) {
    // Modify the GameManager
    Card* card = _posed[cardPosition%MAX_POSED_CARD];

    if(targetPosition == -1) {
        _adverseHeal = heal;
        wizardDisplay->attackPlayer(card);
    } else {
        Card* ennemyCard = _ennemyPosed[targetPosition%MAX_POSED_CARD];
        ennemyCard->setHP(heal);
        wizardDisplay->attackCard(card, ennemyCard);
    }
}

/**
 * Call when adverse card attack an other or adverse player
 *
 * @param cardPosition the card wich make attack
 * @param targetPosition the card wich IS attack (-1 for advers player)
 * @param heal of the target at end
 */
void GameManager::adverseAttackCard(unsigned cardPosition, int targetPosition, unsigned heal) {
    Card* card = _ennemyPosed[cardPosition%MAX_POSED_CARD];
    if(targetPosition == -1) {
        _heal = heal;
        wizardDisplay->adverseAttackPlayer(card);
    } else {
        Card* ennemyCard = _posed[targetPosition%MAX_POSED_CARD];
        ennemyCard->setHP(heal);
        wizardDisplay->adverseAttackCard(card, ennemyCard);
    }

}

