#ifndef LIFECURSE_HPP
#define	LIFECURSE_HPP

#include "common/Card.hpp"
#include "common/CardCreature.hpp"
#include "server/Effect.hpp"

class LifeCurse : public Effect{

    std::size_t _lifeValue;
public:
    LifeCurse(std::size_t lifeValue=1):_lifeValue(lifeValue){};
    ~LifeCurse(){};

    virtual void apply(Card*) override;
};

void LifeCurse::apply(Card* target){
    target->setMaxLife(_lifeValue);
    if (target->getLife() > _lifeValue ){
        target->setLife(_lifeValue);
    }
}

#endif	/* LIFECURSE_HPP */