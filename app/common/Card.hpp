#ifndef CARD_HPP
#define	CARD_HPP

#include <string>
#include <map>
#include <cstddef>
//#include "Effect.hpp"


/**
 * One class per card.  Contain all informations of the card
 */
class Card {
public:
    // Default constructor ?
    Card(std::size_t id, std::string name, std::size_t energy,/*Effect effect, //TODO tmp patch*/ bool);

    Card(Card& card); // copy contructor


private:
    std::size_t _id; // id or the cards
    std::string _name; // name of the cards
    std::size_t _energyCost;
    int _effect;//TODO tmp patch Effect _effect; // His special effect


public:
    virtual void applyEffect(Card& card);
    virtual ~Card() = 0; // Abstract class because we cann't instance it

    std::size_t getId(){return _id;}
    std::string getName(){return _name;}
    std::size_t getEnergyCost(){return _energyCost;}
    //TODO tmp patch Effect getEffect(){return _effect;}

    //void setEnergyCost(std::size_t newCost){_energyCost = newCost}
    // maybe be able to change with spell cards (see that later)

};


//Card::~Card() = default;




#endif	/* CARD_HPP */
