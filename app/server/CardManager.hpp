
#ifndef CARDMANAGER_HPP
#define	CARDMANAGER_HPP

#include <map>


#include "Effect.hpp"
#include "../common/Card.hpp"

/**
 * Load and save Card on file
 * (Must not be a Class #JavaPower)
 */
class CardManager {

    static std::map<int, Card&> listCard; // List of card (with id and card)


public:
    static void loadCards();
    virtual Card& loadCard(std::size_t id);


    virtual ~CardManager() = default;
};




#endif	/* CARDMANAGER_HPP */

