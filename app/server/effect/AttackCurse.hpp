#ifndef ATTACKCURSE_HPP
#define	ATTACKCURSE_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
class Game;

class AttackCurse : public Effect{

    unsigned int _attackValue;
public:
    AttackCurse(unsigned int attackValue):_attackValue(attackValue){};
    ~AttackCurse(){};

    virtual void apply(CardMonster*, Game*) override;
};

void AttackCurse::apply(CardMonster* target, Game* game){
    target->setAttack(_attackValue);
}

#endif	/* ATTACKCURSE_HPP */
