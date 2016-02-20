#ifndef LIFEBLESSING_HPP
#define	LIFEBLESSING_HPP

#include "common/Card.hpp"
#include "common/CardCreature.hpp"
#include "server/Effect.hpp"

class LifeBlessing : public Effect{

    std::size_t _lifeValue;
public:
    LifeBlessing(std::size_t lifeValue):_lifeValue(lifeValue){};
    ~LifeBlessing(){};

    virtual void apply(CardMonster*) override;
};

void LifeBlessing::apply(CardMonster* target){
    target->setMaxLife(target->getMaxLife()+_lifeValue);
    target->setLife(target->getLife()+_lifeValue);
}

#endif	/* LIFEBLESSING_HPP */