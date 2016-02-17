#ifndef ATTACKBLESSING_HPP
#define	ATTACKBLESSING_HPP

#include "common/Card.hpp"
#include "common/CardCreature.hpp"
#include "server/Effect.hpp"

class AttackBlessing : public Effect{

    std::size_t _attackValue;
public:
    AttackBlessing(std::size_t attackValue):_attackValue(attackValue){};
    ~AttackBlessing(){};

    virtual void apply(Card*) override;
};

void AttackBlessing::apply(Card* target){
    target->setAttack(target->getAttack()+_attackValue);
}

#endif	/* ATTACKBLESSING_HPP */