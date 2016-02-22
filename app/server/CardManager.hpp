#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

#include "Card.hpp" //TODO tmp patch
#include "CardMonster.hpp"
#include <map>
#include "include/json.hpp"
#include <fstream>

using json = nlohmann::json;

class CardManager{
private:
	static std::map<std::size_t, Card*> listCard; // List of cards (with id and card)

public:
	 ///// STATIC /////
    static Card* getCardById(unsigned int id); // Get a specific card (identified by ID)

    static void loadAllCards();
};

#endif
