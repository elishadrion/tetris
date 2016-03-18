#include "Collection.hpp"

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
Collection::Collection(std::vector<unsigned> listIdCard) {
    for(unsigned int i = 0; i < listIdCard.size(); ++i) {
        _listCard.push_back(CardManager::getCardById(listIdCard[i]));
    }
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
    if(_listCard.size() <= (MAX_CARDS*2)) {
        int nbrCard = static_cast<int>(
            std::count(_listCard.begin(), _listCard.end(), card));
        if(nbrCard < MAX_COPY_CARD) {
            _listCard.push_back(card);
            res = Error::NoError;
        } else {
            res = Error::SameCardMax;
        }
    } else {
        res = Error::CollectionFull;
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
    bool fini = false;

    unsigned i = 0;
    unsigned taille = _listCard.size();
    while(i < taille && !fini) {
        Card* elem = _listCard[i];
        if(elem == card) {
            _listCard[i] = _listCard[taille-1];
            _listCard.pop_back();
            fini = true;
        }
        ++i;
    }
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
        res = static_cast<int>(std::distance(_listCard.begin(), it));
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

std::vector<unsigned> Collection::getCardsId() const {
    std::vector<unsigned> res;
    for (size_t i = 0; i < _listCard.size(); ++i) {
        res.push_back(_listCard.at(i) -> getId());
    }
    return res;
}

/**
 * Get the number of card in the collection
 */
unsigned Collection::size() {
    return _listCard.size();
}
