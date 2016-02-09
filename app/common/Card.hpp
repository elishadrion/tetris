
#ifndef CARD_HPP
#define	CARD_HPP

#include <string>
#include <map>
#include <cstddef>


/**
 * One class per card.  Contain all informations of the card
 */
class Card {

    static std::map<std::size_t, Card*> listCard; // List of card (with id and card)


public:
    // Default constructor ?
    Card(std::size_t id, std::string name, std::size_t energy, std::size_t heal,
        std::string effect, bool);

    Card(Card& card); // copy contructor


    ///// STATIC /////
    static Card* getCard(std::size_t id); // Get a specific card (identified by ID)


private:
    std::size_t _id; // id or the cards
    std::string _name; // name of the cards
    std::size_t _energyCost;
    std::size_t _heal;
    std::string _effect; // His special effect


public:
    virtual ~Card() = 0; // Abstract class because we cann't instance it
};


//Card::~Card() = default;




#endif	/* CARD_HPP */
