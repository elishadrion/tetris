
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

void Collection::add(Card* card){
	_listAllCards.push_back(card);
}

#endif	/* COLLECTION_HPP */