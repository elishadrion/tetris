#ifndef DAMAGE_HPP
#define	DAMAGE_HPP

#include "common/Card.hpp"
#include "common/CardCreature.hpp"
#include "server/Effect.hpp"
#include "server/PlayerInGame.hpp"

class Damage : public Effect{

    std::size_t _damageValue;
public:
    Damage(std::size_t damageValue=2):_damageValue(damageValue){};
    ~Damage(){};

    virtual void apply(Card*) override;
    virtual void apply(PlayerInGame*);
};

void Damage::apply(Card* target){
    target->setLife(target->getLife()-_damageValue);
}

void Damage::apply(PlayerInGame* target){
    target->setLife(target->getLife()-_damageValue);
}

#endif	/* DAMAGE_HPP */