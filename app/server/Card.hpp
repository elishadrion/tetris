#ifndef CARD_HPP
#define	CARD_HPP

#include <string>
#include <map>
#include <cstddef>

#include "Effect.hpp"

class Game;
class CardMonster;
class PlayerInGame;


/**
 * One class per card.  Contain all information of the card
 */
class Card {
public:
    // Default constructor ?
    Card(unsigned int id, std::string name, unsigned int energy,int effect, bool);
    Card(Card& card) = default; // copy contructor
    Card& operator=(const Card&) = default; // copy operator


private:
    unsigned int _id; // id of the card
    std::string _name; // name of the card
    unsigned int _energyCost;
    Effect* _effect; // Its special effect


public:
    virtual void applyEffect(CardMonster* cardmonster, Game*);
    virtual void applyEffect(PlayerInGame* player, Game*);
    virtual ~Card();

    unsigned int getId() const {return _id;}
    std::string getName() const {return _name;}
    unsigned int getEnergyCost(){return _energyCost;}
    bool gotEffect();
    int getEffectID();
    virtual bool isMonster() { return false; }

    virtual bool canBeApplyOnCard();
    virtual bool canBeApplyOnPlayer();

    virtual Card* clone();

    //void setEnergyCost(unsigned int newCost){_energyCost = newCost}
    // maybe be able to change with spell cards (see that later)

};






#endif	/* CARD_HPP */
