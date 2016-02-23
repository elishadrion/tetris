#ifndef HEAL_HPP
#define	HEAL_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
#include "server/PlayerInGame.hpp"

class Heal : public Effect{

    unsigned int _healValue;
public:
    Heal(unsigned int healValue):_healValue(healValue){};
    ~Heal(){};

    virtual void apply(CardMonster* target) override;
    virtual void apply(PlayerInGame* target);
    virtual bool canBeApplyOnPlayer() override {return true;};
};

void Heal::apply(CardMonster* target) {
    target->setLife(target->getLife()+_healValue);

    if (target->getLife() > target->getMaxLife()){
    	//Target's life can't be higher than its maximum hp
    	target->setLife(target->getMaxLife());
    }
}

void Heal::apply(PlayerInGame* target) {
    target->getHealed(_healValue);
}

#endif	/* HEAL_HPP */
