#ifndef CARD_HPP
#define	CARD_HPP

#include <string>
#include <map>
#include <cstddef>

#include "Effect.hpp"


class CardMonster;
class PlayerInGame;


/**
 * One class per card.  Contain all information of the card
 */
class Card {
public:
    // Default constructor ?
    Card(unsigned int id, std::string name, unsigned int energy,int effect, bool);

    Card(Card& card); // copy contructor


private:
    unsigned int _id; // id of the card
    std::string _name; // name of the card
    unsigned int _energyCost;
    Effect* _effect; // Its special effect
    bool _taunt;


public:
    virtual void applyEffect(CardMonster& cardmonster);
    virtual void applyEffect(PlayerInGame& player);
    virtual ~Card() = 0; // Abstract class because we can't instance it

    unsigned int getId(){return _id;}
    std::string getName(){return _name;}
    unsigned int getEnergyCost(){return _energyCost;}
    bool gotEffect();
    int getEffectID();
    virtual bool isMonster() { return false; }
    virtual bool isTaunt() { return _taunt; }
    virtual bool canBeApplyOnCard();
    virtual bool canBeApplyOnPlayer();

    //void setEnergyCost(unsigned int newCost){_energyCost = newCost}
    // maybe be able to change with spell cards (see that later)

};






#endif	/* CARD_HPP */
