#ifndef LIFEBLESSING_HPP
#define	LIFEBLESSING_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"

class LifeBlessing : public Effect{

    unsigned int _lifeValue;
public:
    LifeBlessing(unsigned int lifeValue):_lifeValue(lifeValue){};
    ~LifeBlessing(){};

    virtual void apply(CardMonster*) override;
};

void LifeBlessing::apply(CardMonster* target){
    target->setMaxLife(target->getMaxLife()+_lifeValue);
    target->setLife(target->getLife()+_lifeValue);
}

#endif	/* LIFEBLESSING_HPP */
