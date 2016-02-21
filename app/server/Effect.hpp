#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "Card.hpp"
#include <vector>


class CardMonster;
class PlayerInGame;

class Effect { //Abstract class
    static std::vector<Effect*> listEffect;
public:
    Effect(){
    //Attention, vérifier si classes filles appellent cosntructeur parent
        listEffect.push_back(this);
    };
    virtual ~Effect(){};

    static void loadAllEffect();
    static Effect* getEffectByID(unsigned);

    virtual void apply(CardMonster*) = 0;
    virtual bool isTaunt(){return false;};
    virtual bool canBeApplyOnPlayer(){return false;};
    virtual bool canBeApplyOnPCard(){return true;};
};



#endif  /* EFFECT_HPP */
