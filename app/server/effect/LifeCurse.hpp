#ifndef LIFECURSE_HPP
#define	LIFECURSE_HPP

#include "server/Card.hpp"
#include "server/CardCreature.hpp"
#include "server/Effect.hpp"

class LifeCurse : public Effect{

    std::size_t _lifeValue;
public:
    LifeCurse(std::size_t lifeValue):_lifeValue(lifeValue){};
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
