#ifndef LIFEBLESSING_HPP
#define	LIFEBLESSING_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
class Game;

class LifeBlessing : public Effect{

    unsigned int _lifeValue;
public:
    LifeBlessing(unsigned int lifeValue):_lifeValue(lifeValue){}
    ~LifeBlessing(){}

    virtual void apply(CardMonster*, Game*) override;
};

/**
 * Apply a bless on the monster life, the monster life is increased
 *
 * @param target : the monster on which the effect will be apply
 * @param game : the game where the effect will be apply
 * @return void 
 */
void LifeBlessing::apply(CardMonster* target, Game* game){
    target->setMaxLife(target->getMaxLife()+_lifeValue);
    target->setLife(target->getLife()+_lifeValue);
}

#endif	/* LIFEBLESSING_HPP */
