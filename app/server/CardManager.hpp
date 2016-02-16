#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

#include "Card.hpp"

class CardManager{
private:
	static std::map<std::size_t, Card*> listCard; // List of card (with id and card)

public:
	 ///// STATIC /////
    static Card* getCardById(std::size_t id); // Get a specific card (identified by ID)

    static Effect* getEffectByID(std::size_t id);
};

#endif