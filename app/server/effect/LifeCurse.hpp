#ifndef LIFECURSE_HPP
#define	LIFECURSE_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
class Game;

class LifeCurse : public Effect{

    unsigned int _lifeValue;
public:
    LifeCurse(unsigned int lifeValue):_lifeValue(lifeValue){}
    ~LifeCurse(){}

    virtual void apply(CardMonster*, Game*) override;
};

/**
 * Apply a curse on the monster life, the monster life is decreased
 *
 * @param target : the monster on which the effect will be apply
 * @param game : the game where the effect will be apply
 * @return void 
 */
void LifeCurse::apply(CardMonster* target, Game* game){
    target->setMaxLife(_lifeValue);
    if (target->getLife() > _lifeValue){
        target->setLife(_lifeValue);
    }
}

#endif	/* LIFECURSE_HPP */
