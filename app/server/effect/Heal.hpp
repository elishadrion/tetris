#ifndef HEAL_HPP
#define	HEAL_HPP

#include "server/Card.hpp"
#include "server/CardCreature.hpp"
#include "server/Effect.hpp"
#include "server/PlayerInGame.hpp"

class Heal : public Effect{

    std::size_t _healValue;
public:
    Heal(std::size_t healValue):_healValue(healValue){};
    ~Heal(){};

    virtual void apply(CardMonster* target) override;
    virtual void apply(PlayerInGame* target);
    virtual bool canBeApplyOnPlayer() override {return true;};
};

void Heal::apply(CardMonster* target) {
    target->setLife(target->getLife()+_healValue);

    if (target->getlife() > target->getMaxLife()){
    	//Target's life can't be higher than its maximum hp
    	target->setLife(target->getMaxLife());
    }
}

void Heal::apply(PlayerInGame* target) {
	std::size_t maxHpPlayer=20;
    target->setLife(target->getLife()+_healValue);

    if (target->getlife() > maxHpPlayer){
    	//Target's life can't be higher than its maximum hp
    	target->setLife(maxHpPlayer);
    }
}

#endif	/* HEAL_HPP */
