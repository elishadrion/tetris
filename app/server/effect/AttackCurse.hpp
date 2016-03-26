#ifndef ATTACKCURSE_HPP
#define	ATTACKCURSE_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
class Game;

class AttackCurse : public Effect{

    unsigned int _attackValue;
public:
    AttackCurse(unsigned int attackValue):_attackValue(attackValue){}
    ~AttackCurse(){}

    virtual void apply(CardMonster*, Game*) override;
};

/**
 * Apply a curse on the monster attack, the monster attack is decreased
 *
 * @param target : the monster on which the effect will be apply
 * @param game : the game where the effect will be apply
 * @return void 
 */
void AttackCurse::apply(CardMonster* target, Game* game){
    target->setAttack(_attackValue);
}

#endif	/* ATTACKCURSE_HPP */
