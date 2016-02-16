#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

#include "common/Card.hpp" //TODO tmp patch

class CardManager{
private:
	static std::map<std::size_t, Card*> listCard; // List of card (with id and card)

public:
	 ///// STATIC /////
    static Card* getCardById(std::size_t id); // Get a specific card (identified by ID)

    //TODO tmp patch static Effect* getEffectByID(std::size_t id);
};

#endif
