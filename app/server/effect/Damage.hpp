#ifndef DAMAGE_HPP
#define	DAMAGE_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
#include "server/PlayerInGame.hpp"

class Damage : public Effect{

    unsigned int _damageValue;
public:
    Damage(unsigned int damageValue):_damageValue(damageValue){};
    ~Damage(){};

    virtual void apply(CardMonster*) override;
    virtual void apply(PlayerInGame*);
    virtual bool canBeApplyOnPlayer() override {return true;};
};

void Damage::apply(CardMonster* target){
    target->setLife(target->getLife()-_damageValue);
}

void Damage::apply(PlayerInGame* target){
    target->takeDamage(damageValue);
}

#endif	/* DAMAGE_HPP */
