
#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <vector>

#include "CardManager.hpp"


class Card;
#include "Card.hpp"

class Collection {
public:
    std::vector<Card*>_listCard;

public:
    Collection();
    Collection(std::vector<Card*>);
    Collection(std::vector<int>);
    Collection(const Collection&); // Copy constructor
    Collection& operator=(const Collection&); // Copy operator
    void addCard(Card*); // adds a card in the deck
    void addCard(int cardId); // add a card in the collection with the id
    void removeCard(int i); // removes the i-th card from the deck
    void removeCard(Card*); // removes a card from the deck
    void removeCardId(int cardId);
    int indexOfCard(int cardId); // the index of a card
    int getCardIndex(Card*); // get the index of the card
};

#endif  /* COLLECTION_HPP */
