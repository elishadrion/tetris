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

    for(unsigned i = 0; i < MAX_POSED_CARD; ++i) {
        _posed[i] = nullptr;
        _ennemyPosed[i] = nullptr;
    }

    _instance = this;
}

Card* GameManager::getCardOnPosition(unsigned pos) {
    Card* res = nullptr;
    Card* posed = _posed[pos%MAX_POSED_CARD];
    Card* advPosed = _ennemyPosed[pos%MAX_POSED_CARD];

    if(posed != nullptr && posed->getPosition() == pos) {
        res = posed;
    } else if(advPosed != nullptr && advPosed->getPosition() == pos) {
        res = advPosed;
    }

    return res;
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

    int valeurEnergy = nbrTurn;
    if(valeurEnergy > MAX_ENERGY) {
        valeurEnergy = MAX_ENERGY;
    }

    if(_isTurn) {
        _energy = valeurEnergy;
        _adverseEnergy = 0;
    } else {
        _adverseEnergy = valeurEnergy;
        _energy = 0;
    }

    wizardDisplay->changeTurn();
}

/**
 * Call when the server inform that the player draw a card
 *
 * @param idCard of the draw card
 */
void GameManager::drawCard(unsigned idCard) {
    Card* card = new Card(*CacheManager::getCard(idCard));
    _hand.push_back(card);
    wizardDisplay->drawCard(card);
}



/**
 * Remove a card from the hand of the player
 *
 * @param card which must be remove
 * @return the removed card
 */
Card* GameManager::removeCardFromHand(Card* card) {
    return removeCardFromHand(card->getID());
}

/**
 * Remove a card from the hand of the player
 *
 * @param idCard which card id must be remove
 * @return the removed card
 */
Card* GameManager::removeCardFromHand(unsigned idCard) {
    Card* res = nullptr;
    bool fini = false;

    unsigned i = 0;
    unsigned taille = _hand.size();
    Card* elem;
    while(i < taille && !fini) {
        elem = _hand[i];
        if(elem->getID() == idCard) {
            res = _hand[i];
            _hand[i] = _hand[taille-1];
            _hand.pop_back();
            fini = true;
        }
        ++i;
    }


    return res;
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
    Card* card = removeCardFromHand(static_cast<unsigned>(cardID));

    card->setPosition(position);
    _posed[position%MAX_POSED_CARD] = card;
    _energy -= card->getEnergyCost();
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

    Card* card = removeCardFromHand(cardID);;

    if(!isEffectCard) {
        card->setPosition(position);
        _posed[position%MAX_POSED_CARD] = card;
    }

    _energy -= card->getEnergyCost();
    if(targetPosition == -1) {
        _adverseHeal = heal;
    } else {
        Card* enemyCard = getCardOnPosition(static_cast<unsigned>(targetPosition));
        if(enemyCard != nullptr) {
            enemyCard->setHP(heal);

            WizardLogger::info("Vie de la carte adverse: " + std::to_string(enemyCard->getHP()));
            if(enemyCard->isDead()) {
                _advTrash.push_back(enemyCard);
                wizardDisplay->cardIsDead(enemyCard, true);
            }
        } else {
            WizardLogger::warning("Carte en position " +
                                  std::to_string(targetPosition) + " introuvable");
        }
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
        // get card on position
        Card* enemyCard = getCardOnPosition(static_cast<unsigned>(targetPosition));
        if(enemyCard != nullptr) {
            enemyCard->setHP(heal);
            if(isEffectCard) {
                wizardDisplay->placeAdverseSpellCard(card, enemyCard);
            } else {
                wizardDisplay->placeAdverseCardAndAttack(card, enemyCard);
            }

            if(enemyCard->isDead()) {
                _trash.push_back(enemyCard);
                wizardDisplay->cardIsDead(enemyCard, false);
            }
        } else {
            WizardLogger::warning("Carte adverse en position " +
                                  std::to_string(targetPosition) + " introuvable");
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
void GameManager::attackCard(unsigned cardPosition, unsigned cardHeal,
                             int targetPosition, unsigned targetHeal) {
    // Modify the GameManager
    Card* card = _posed[cardPosition%MAX_POSED_CARD];

    _energy -= card->getEnergyCost();
    card->setHP(cardHeal);
    if(targetPosition == -1) {
        _adverseHeal = targetHeal;
    } else {
        Card* ennemyCard = _ennemyPosed[targetPosition%MAX_POSED_CARD];
        ennemyCard->setHP(targetHeal);
        if(ennemyCard->isDead()) {
            wizardDisplay->cardIsDead(ennemyCard, true);
        }
    }
    if(card->isDead()) {
        wizardDisplay->cardIsDead(card, false);
    }
}

/**
 * Call when adverse card attack an other or adverse player
 *
 * @param cardPosition the card wich make attack
 * @param targetPosition the card wich IS attack (-1 for advers player)
 * @param heal of the target at end
 */
void GameManager::adverseAttackCard(unsigned cardPosition, unsigned cardHeal,
                                    int targetPosition, unsigned targetHeal) {
    Card* card = _ennemyPosed[cardPosition%MAX_POSED_CARD];

    _adverseEnergy -= card->getEnergyCost();
    card->setHP(cardHeal);
    if(targetPosition == -1) {
        _heal = targetHeal;
        wizardDisplay->adverseAttackPlayer(card);
    } else {
        Card* ennemyCard = _posed[targetPosition%MAX_POSED_CARD];
        ennemyCard->setHP(targetHeal);
        wizardDisplay->adverseAttackCard(card, ennemyCard);
        if(ennemyCard->isDead()) {
            wizardDisplay->cardIsDead(ennemyCard, false);
        }
    }
    if(card->isDead()) {
        wizardDisplay->cardIsDead(card, true);
    }

}

/**
 * Call when a player loose heal
 *
 * @param heal new amount of heal
 * @param adverse player or not
 */
void GameManager::playerDamage(unsigned heal, bool adverse) {
    if(adverse) {
        _adverseHeal = heal;
        wizardDisplay->advPlayerDamage();
    } else {
        _heal = heal;
        wizardDisplay->playerDamage();
    }
}
