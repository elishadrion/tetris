#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

#include "Card.hpp" //TODO tmp patch
#include "CardMonster.hpp"
#include <map>
#include "include/json.hpp"
#include <fstream>
#include <time.h>
#include <stdlib.h>


using json = nlohmann::json;

class CardManager{
private:
	static std::map<unsigned, Card*> _listCard; // List of cards (with id and card)

public:
	 ///// STATIC /////
    static Card* getCardById(unsigned int id); // Get a specific card (identified by ID)

    static void loadAllCards();
    
    static Card* chooseCardWin();
};

#endif
