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

/**
 * Apply a bless on the monster attack, the monster attack is increased
 *
 * @param target : the monster on which the effect will be apply
 * @param game : the game where the effect will be apply
 * @return void 
 */
void AttackBlessing::apply(CardMonster* target, Game* game){
    target->setAttack(target->getAttack()+_attackValue);
}

#endif	/* ATTACKBLESSING_HPP */
