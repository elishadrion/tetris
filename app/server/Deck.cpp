
#include <algorithm>    // std::find
#include <stdexcept>

#include "Deck.hpp"

/**
 * Constructor
 *
 * @param name of the deck
 * @param listCard the must be add on deck
 */
Deck::Deck(std::string name, std::vector<Card*> listCard):
    Collection(listCard), _name(name) { }

/**
 * Constructor
 *
 * @param name of the deck
 * @param listCard the must be add on deck
 */
Deck::Deck(std::string name, std::vector<int> listCard):
    Collection(listCard), _name(name) { }

/**
 * Copy Constructor
 *
 * @param deck to copy
 */
Deck::Deck(const Deck& deck): Collection(deck),
    _name(deck._name) {}


/**
 * The name of the deck
 *
 * @return the name of the deck
 */
std::string Deck::getName() {
    return _name;
}


/**
 * Checks if the deck is valide.
 * He must have 100 cards
 *
 * @return True if the deck is valide
 */
bool Deck::isValide() {
    return _listCard.size() == 20;
}


/**
 * Returns the last card of the deck
 *
 * @return the id of the card or -1 if empty
 */
Card* Deck::pickup() {
    Card* card;
    if(_listCard.size() > 0) {
        int chooseCard = rand() % static_cast<int>(_listCard.size()); // Chose random index
        card = getCardOnIndex(chooseCard); // gets id
        removeCard(chooseCard); // Removes the card
    }

    return card; // Returns the id
}


/**
 * Adds a card in the deck
 *
 * @param card the card to add
 * @return Error and NoError if all is ok
 */
Error Deck::addCard(Card* card) {
    Error res;
    if(_listCard.size() >= 20) {
        WizardLogger::error("Un deck a maximum 20 cartes");
        res = Error::DeckFull;
    } else {
        res = Collection::addCard(card);
    }

    return res;
}


/**
 * Adds a card in the deck
 *
 * @param cardId the id of the card to add
 * @return Error and NoError if all is ok
 */
Error Deck::addCard(int cardId) {
    return addCard(CardManager::getCardById(cardId));
}


/**
 * Copy the deck AND all the card !
 *
 * @return the new deck
 */
Deck* Deck::copyDeck() {
    std::vector<Card*> newCardList;
    for(unsigned i = 0; i < _listCard.size(); ++i) {
        Card* currentCard = _listCard[i];
        newCardList.push_back(new Card(*currentCard));
    }

    return new Deck(_name, newCardList);
}

/**
 * Get the deck with a specific name
 *
 * @param name of the deck
 * @param listDeck to find the deck with the specific name
 * @return the deck or nullptr
 */
Deck* Deck::getDeck(std::string name, std::vector<Deck*> listDeck) {
    Deck* res = nullptr;

    unsigned i = 0;
    while(res == nullptr && i < listDeck.size()) {
        Deck* currentDeck = dynamic_cast<Deck*>(listDeck[i]);
        if(currentDeck->getName() == name) {
            res = currentDeck;
        }
        ++i;
    }

    return res;
}

