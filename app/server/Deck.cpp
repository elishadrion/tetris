
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
 * Copy Constructor
 *
 * @param deck to copy
 */
Deck::Deck(const Deck& deck): Collection(deck),
    _name(deck._name) {}


/**
 * Copy operator
 *
 * @param deck to copy
 */
Deck& Deck::operator=(const Deck& deck) {
    _name = deck._name;
    _listCard = deck._listCard;
}


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

/*
/**
 * Removes a card from the deck
 *
 * @param i position of the card in the deck
 *
void Deck::removeCard(const int i) {
    _listCard.erase(_listCard.begin() + i);
}


/**
 * Removes a card from the deck
 *
 * @param id the id of the card in the deck
 * @see removeCard (better)
 *
void Deck::removeIdCard(const int id) {
    removeCard(indexOfCard(id));
}

/**
 * Gets the index of a card in the deck
 *
 * @param id the card id
 * @return index of the card (-1 if not found)
 *
int Deck::indexOfCard(const int id) {
    std::vector<unsigned int>::iterator it = std::find(_listCard.begin(), _listCard.end(), id);
    if(it != _listCard.end()) {
        return *it;
    }
    return -1;
}

/**
 * Gets the id of the card at the position in parameter
 *
 * @param i the position
 * @return the id of the card
 *
int Deck::getIdOnIndex(const int i) {
    return _listCard[i];
}
*/


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
 * Error: OverFlow if more than 20 cards
 *
 * @param card the card to add
 * @return True if we can add card.
 */
bool Deck::addCard(Card* card) {
    bool res = false;
    if(_listCard.size() >= 20) {
        WizardLogger::error("Un deck a maximum 20 cartes");
        throw std::overflow_error("A deck has maximum 20 cards");
    } else {
        res = Collection::addCard(card);
    }

    return res;
}

/**
 * Copy the deck AND all the card !
 *
 * @return the new deck
 */
Deck* Deck::copyDeck() {
// TO DO
}

/**
 * Get the deck with a specific name
 *
 * @param name of the deck
 * @param listDeck to find the deck with the specific name
 * @return the deck or nullptr
 */
Deck* Deck::getDeck(std::string name, std::vector<Deck*> listDeck) {
    Deck* res;

    // TO DO

    return res;
}

