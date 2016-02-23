
#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <vector>
class Card;

class Collection {

    std::vector<Card*> _listAllCards;
public:

    Collection(){};
    ~Collection(){};
    void add(Card*);

};

#endif  /* COLLECTION_HPP */
