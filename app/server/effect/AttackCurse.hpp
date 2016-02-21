#ifndef ATTACKCURSE_HPP
#define	ATTACKCURSE_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"

class AttackCurse : public Effect{

    unsigned int _attackValue;
public:
    AttackCurse(unsigned int attackValue):_attackValue(attackValue){};
    ~AttackCurse(){};

    virtual void apply(CardMonster*) override;
};

void AttackCurse::apply(CardMonster* target){
    target->setAttack(_attackValue);
}

#endif	/* ATTACKCURSE_HPP */
