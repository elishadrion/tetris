#ifndef ATTACKCURSE_HPP
#define	ATTACKCURSE_HPP

#include "server/Card.hpp"
#include "server/CardCreature.hpp"
#include "server/Effect.hpp"

class AttackCurse : public Effect{

    std::size_t _attackValue;
public:
    AttackCurse(std::size_t attackValue):_attackValue(attackValue){};
    ~AttackCurse(){};

    virtual void apply(CardMonster*) override;
};

void AttackCurse::apply(CardMonster* target){
    target->setAttack(_attackValue);
}

#endif	/* ATTACKCURSE_HPP */
