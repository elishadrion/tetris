#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <vector>
/*
#include "CardMonster.hpp"
#include "PlayerInGame.hpp"
#include "effect/Taunt.hpp"
#include "effect/Heal.hpp"
#include "effect/Damage.hpp"
#include "effect/LifeBlessing.hpp"
#include "effect/LifeCurse.hpp"
#include "effect/AttackBlessing.hpp"
#include "effect/AttackCurse.hpp"
#include "effect/Draw.hpp"
*/


class CardMonster;
class PlayerInGame;


class Effect { //Abstract class
    static std::vector<Effect*> _listEffect;
    unsigned _id = -1;

public:
    Effect(){
        //Attention, vérifier si classes filles appellent cosntructeur parent
        _listEffect.push_back(this);
        _id = (_listEffect.size()-1);
    };
    unsigned getId() { return _id; }
    virtual ~Effect(){};

    static void loadAllEffect();
    static Effect* getEffectByID(unsigned);

    virtual void apply(CardMonster*) = 0;
    virtual void apply(PlayerInGame*) {}; //TO DO (error by default)
    virtual bool isTaunt(){return false;};
    virtual bool canBeApplyOnPlayer(){return false;};
    virtual bool canBeApplyOnCard(){return true;};
};



#endif  /* EFFECT_HPP */
