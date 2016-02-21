
#ifndef COLLECTION_HPP
#define	COLLECTION_HPP

#include <vector>
#include "Card.hpp"

class Collection {

    std::vector<Card*> _listAllCards;
public:

    Collection(){};
    ~Collection(){};
    void add(Card*);

};

#endif	/* COLLECTION_HPP */