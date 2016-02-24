
#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <vector>

#include "common/Error.hpp"


#include "CardManager.hpp"
class Card;
#include "Card.hpp"

class Collection {
protected:
    std::vector<Card*>_listCard;

public:
    Collection();
    Collection(std::vector<Card*>);
    Collection(std::vector<int>);
    Collection(const Collection&); // Copy constructor
    Collection& operator=(const Collection&); // Copy operator
    virtual Error addCard(Card*); // adds a card in the deck
    virtual Error addCard(int cardId); // add a card in the collection with the id
    void removeCard(int i); // removes the i-th card from the deck
    void removeCard(Card*); // removes a card from the deck
    void removeCardId(int cardId);
    int indexOfCard(int cardId); // the index of a card
    int getCardIndex(Card*); // get the index of the card
    Card* getCardOnIndex(const unsigned index);

    virtual ~Collection() = default;
};

#endif  /* COLLECTION_HPP */
