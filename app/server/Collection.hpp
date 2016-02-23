
#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <vector>
class Card;

class Collection {
public:

    Collection(){};
    ~Collection(){};
    //void add(Card*);



    std::vector<*Card>_listCard;

    // TO DO

private:
    void removeCard(int i); // removes the i-th card from the deck
    void removeCard(Card*); // removes a card from the deck
    int indexOfCard(int id); // the index of a card
    int getCardIndex(Card*); // get the index of the card

public:
    Collection(const Collection&); // Copy constructor
    Collection& operator=(const Collection&); // Copy operator
    void addCard(Card*); // adds a card in the deck
    void addCard(int cardId); // add a card in the collection with the id


};

#endif  /* COLLECTION_HPP */
