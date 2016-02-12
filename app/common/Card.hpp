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

    static std::map<std::size_t, Card*> listCard; // List of card (with id and card)


public:
    // Default constructor ?
    Card(std::size_t id, std::string name, std::size_t energy,std::size_t heal, std::string effect, bool);
    Card(Card& card); // copy contructor


    ///// STATIC /////
    static Card* getCard(std::size_t id); // Get a specific card (identified by ID)


private:
    std::size_t _id; // id or the cards
    std::string _name; // name of the cards
    std::size_t _energyCost;
    std::string _effect; // His special effect
    std::size_t _heal;


public:
    virtual void applyEffect(Card& card) {}
    virtual ~Card() = 0; // Abstract class because we cann't instance it

    std::size_t getId(){return _id;}
    std::string getName(){return _name;}
    std::size_t getEnergyCost(){return _energyCost;}
    std::string getEffect(){return _effect;}
    std::size_t getLife() {}
    void setLife(std::size_t) {}
    std::size_t getMaxLife() {}
    void setMaxLife(std::size_t) {}
    std::size_t getAttack() {}
    void setAttack(std::size_t) {}

    //void setEnergyCost(std::size_t newCost){_energyCost = newCost}
    // maybe be able to change with spell cards (see that later)
};



//Card::~Card() = default;




#endif	/* CARD_HPP */
