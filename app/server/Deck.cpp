
#include <algorithm>    // std::find
#include <stdexcept>

#include "Deck.hpp"


/**
 * Checks if the deck is valide.
 * He must have 100 cards
 *
 * @return True if the deck is valide
 */
bool Deck::isValide() {
    return _listCard.size() == 100;
}

/**
 * Removes a card from the deck
 *
 * @param i position of the card in the deck
 */
void Deck::removeCard(const int i) {
    _listCard.erase(_listCard.begin() + i);
}


/**
 * Removes a card from the deck
 *
 * @param id the id of the card in the deck
 * @see removeCard (better)
 */
void Deck::removeIdCard(const int id) {
    removeCard(indexOfCard(id));
}

/**
 * Gets the index of a card in the deck
 *
 * @param id the card id
 * @return index of the card (-1 if not found)
 */
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
 */
int Deck::getIdOnIndex(const int i) {
    return _listCard[i];
}


/**
 * Returns the last card of the deck
 *
 * @return the id of the card
 */
int Deck::pickup() {
    int chooseCard = rand() % static_cast<int>(_listCard.size()); // Chose random index
    int id = getIdOnIndex(chooseCard); // gets id
    removeCard(chooseCard); // Removes the card
    return id; // Returns the id
}

/**
 * Adds a card in the deck
 * Error: OverFlow if more than 100 cards
 *
 * @param id of the card
 */
void Deck::addCard(const int id) {
    if(_listCard.size() == 100) {
        WizardLogger::error("Un deck a maximum 100 cartes");
        throw std::overflow_error("A deck has maximum 100 cards");
    }
    _listCard.push_back(id);
}

/**
 * Copy Constructor
 *
 * @param deck to copy
 */
Deck::Deck(const Deck& deck):
    _listCard(deck._listCard), _name(deck._name) {}


/**
 * Copy operator
 *
 * @param deck to copy
 */
Deck& Deck::operator=(const Deck& deck) {
    _name = deck._name;
    _listCard = deck._listCard;
}
