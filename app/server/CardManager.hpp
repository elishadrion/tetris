#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

#include "common/Card.hpp" //TODO tmp patch
#include <map>
#include "include/json.hpp"

using json = nlohmann::json;

class CardManager{
private:
	static std::map<std::size_t, Card*> listCard; // List of cards (with id and card)

public:
	 ///// STATIC /////
    static Card* getCardById(std::size_t id); // Get a specific card (identified by ID)

    static void loadAllCards();
};

#endif