#ifndef LIFECURSE_HPP
#define	LIFECURSE_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"

class LifeCurse : public Effect{

    unsigned int _lifeValue;
public:
    LifeCurse(unsigned int lifeValue):_lifeValue(lifeValue){};
    ~LifeCurse(){};

    virtual void apply(CardMonster*) override;
};

void LifeCurse::apply(CardMonster* target){
    target->setMaxLife(_lifeValue);
    if (target->getLife() > _lifeValue ){
        target->setLife(_lifeValue);
    }
}

#endif	/* LIFECURSE_HPP */
