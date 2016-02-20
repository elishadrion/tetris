#ifndef CARD_HPP
#define	CARD_HPP

#include <string>
#include <map>
#include <cstddef>

#include "server/Effect.hpp"


class CardMonster;
class PlayerInGame;


/**
 * One class per card.  Contain all information of the card
 */
class Card {
public:
    // Default constructor ?
    Card(std::size_t id, std::string name, std::size_t energy,int effect, bool);

    Card(Card& card); // copy contructor


private:
    std::size_t _id; // id of the card
    std::string _name; // name of the card
    std::size_t _energyCost;
    int _effect;// Its special effect ID
    bool _taunt;


public:
    virtual void applyEffect(CardMonster& cardmonster);
    virtual void applyEffect(PlayerInGame& player);
    virtual ~Card() = 0; // Abstract class because we can't instance it

    std::size_t getId(){return _id;}
    std::string getName(){return _name;}
    std::size_t getEnergyCost(){return _energyCost;}
    bool gotEffect();
    int getEffectID(){return _effect;}
    virtual bool isMonster() { return false; }
    virtual bool isTaunt() { return _taunt; }

    //void setEnergyCost(std::size_t newCost){_energyCost = newCost}
    // maybe be able to change with spell cards (see that later)

};






#endif	/* CARD_HPP */
