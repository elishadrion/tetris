#include "Collection.hpp"


/**
 * Default constructor
 */
Collection::Collection() {}

/**
 * Constructor
 *
 * @param listCard list of card
 */
Collection::Collection(std::vector<Card*> listCard):
    _listCard(listCard) {}

/**
 * Constructor
 *
 * @param listIdCard the list of card ID
 */
Collection::Collection(std::vector<int> listIdCard) {
    for(unsigned int i = 0; i < listIdCard.size(); ++i) {
        _listCard.push_back(CardManager::getCardById(listIdCard[i]));
    }
}

/**
 * Copy constructor
 *
 * @param collection to copy
 */
Collection::Collection(const Collection& collection):
    _listCard(collection._listCard) {}


/**
 * Copy opperator
 *
 * @param col collection to copy
 */
Collection& Collection::operator=(const Collection& col) {
    _listCard = col._listCard;
}


/**
 * Add a Card to the collection
 *
 * @param card the card to add
 * @return True if we can add Card (false if there is more
 * than two cards the same)
 */
Error Collection::addCard(Card* card) {
    Error res;
    int nbrCard = std::count (_listCard.begin(), _listCard.end(), card);
    if(nbrCard < 2) {
        _listCard.push_back(card);
        res = Error::NoError;
    } else {
        res = Error::TwoSameCardMax;
    }

    return res;
}


/**
 * Add a Card to the collection
 *
 * @param cardId the id of the card
 * @return True if we can add Card (false if there is more
 * than two cards the same)
 */
Error Collection::addCard(int cardId) {
    return this->addCard(CardManager::getCardById(cardId));
}


/**
 * Remove a Card on a specific position
 *
 * @param i index of the card
 */
void Collection::removeCard(int i) {
    _listCard.erase(_listCard.begin() + i);
}


/**
 * Remove a Card from the collection
 *
 * @param card the card to remove
 */
void Collection::removeCard(Card* card) {
    _listCard.erase(
        std::remove(_listCard.begin(), _listCard.end(), card),
        _listCard.end());
}


/**
 * Remove a Card from the collection
 *
 * @param cardId the id of the card
 */
void Collection::removeCardId(int cardId) {
    removeCard(CardManager::getCardById(cardId));
}


/**
 * Get the index of one card
 *
 * @param card
 * @return index or -1 if not found
 */
int Collection::getCardIndex(Card* card) {
    int res = -1;

    std::vector<Card*>::iterator it = std::find(_listCard.begin(), _listCard.end(), card);
    if(it != _listCard.end()) {
        res = std::distance(_listCard.begin(), it);
    }

    return res;
}


/**
 * Get the card on the specific index
 *
 * @param index of the card
 * @return the Card at the specific index
 */
Card* Collection::getCardOnIndex(const unsigned index) {
    return _listCard[index];
}

