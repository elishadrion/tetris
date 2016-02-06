
#include "Deck.hpp"
#include <algorithm>    // std::find
#include <stdexcept>

/**
 * Check if the deck is valide.
 * He must to have 100 cards
 * 
 * @return True if the deck is valide
 */
bool Deck::isValide() {
    return _listCard.size() == 100;
}

/**
 * Remove a card from the deck
 * 
 * @param i position of the card in the deck
 */
void Deck::removeCard(const int i) {
    _listCard.erase(_listCard.begin() + i);
}


/**
 * Remove a card from the deck
 * 
 * @param id the id of the card in the deck
 * @see removeCard (better)
 */
void Deck::removeIdCard(const int id) {
    removeCard(indexOfCard(id));
}

/**
 * Get the index of a card in the deck
 * 
 * @param id the card id
 * @return index of the card
 */
int Deck::indexOfCard(const int id) {
    return std::find(_listCard.begin(), _listCard.end(), id);
}

/**
 * Get the id of the card at the position in parameter
 * 
 * @param i the position
 * @return the id of the card
 */
int Deck::getIdOnIndex(const int i) {
    return _listCard[i];
}


/**
 * Return the last card of the deck
 * 
 * @return the id of the card
 */
int Deck::pickup() {
    int chooseCard = rand() % _listCard.size(); // Chose random index
    removeCard(chooseCard); // Remove the card
    return getIdOnIndex(chooseCard); // Return the id
}

/**
 * Add a card on the deck
 * Error: OverFlow if mutch than 100 cards
 * 
 * @param id of the card
 */
void Deck::addCard(const int id) {
    if(_listCard.size() == 100) {
        throw std::overflow_error("A deck has maximum 100 cards");
    }
    _listCard.push_back(id);
}


