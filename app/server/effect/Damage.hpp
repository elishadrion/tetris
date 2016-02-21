#ifndef DAMAGE_HPP
#define	DAMAGE_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
#include "server/PlayerInGame.hpp"

class Damage : public Effect{

    std::size_t _damageValue;
public:
    Damage(std::size_t damageValue=2):_damageValue(damageValue){};
    ~Damage(){};

    virtual void apply(CardMonster*) override;
    virtual void apply(PlayerInGame*);
    virtual bool canBeApplyOnPlayer() override {return true;};
};

void Damage::apply(CardMonster* target){
    target->setLife(target->getLife()-_damageValue);
}

void Damage::apply(PlayerInGame* target){
    target->setLife(target->getLife()-_damageValue);
}

#endif	/* DAMAGE_HPP */
