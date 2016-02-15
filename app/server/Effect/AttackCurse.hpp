#ifndef ATTACKCURSE_HPP
#define	ATTACKCURSE_HPP

#include "common/Card.hpp"
#include "common/CardCreature.hpp"
#include "server/Effect.hpp"

class AttackCurse : public Effect{

    std::size_t _attackValue;
public:
    AttackCurse(std::size_t attackValue=1):_attackValue(attackValue){};
    ~AttackCurse(){};

    virtual void apply(Card*) override;
};

void AttackCurse::apply(Card* target){
    target->setAttack(_attackValue);
}

#endif	/* ATTACKCURSE_HPP */