#ifndef ATTACKBLESSING_HPP
#define	ATTACKBLESSING_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
class Game;

class AttackBlessing : public Effect{

    unsigned int _attackValue;
public:
    AttackBlessing(unsigned int attackValue):_attackValue(attackValue){};
    ~AttackBlessing(){};

    void apply(CardMonster*, Game*) override;
};

void AttackBlessing::apply(CardMonster* target, Game* game){
    target->setAttack(target->getAttack()+_attackValue);
}

#endif	/* ATTACKBLESSING_HPP */
