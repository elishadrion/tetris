#ifndef HEAL_HPP
#define	HEAL_HPP

#include "common/Card.hpp"
#include "common/CardCreature.hpp"
#include "server/Effect.hpp"

class Heal : public Effect{

    std::size_t _healValue;
public:
    Heal(std::size_t healValue=2):_healValue(healValue){};
    ~Heal(){};

    virtual void apply(Card* target) override;
};

void Heal::apply(Card* target) {
    target->setLife(target->getLife()+_healValue);

    if (target->getlife() > target->getMaxLife()){
    	//Target's life can't be higher than its maximum hp
    	target->setLife(target->getMaxLife());
    }
}

#endif	/* HEAL_HPP */