#ifndef HEAL_HPP
#define	HEAL_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
#include "server/PlayerInGame.hpp"
class Game;

class Heal : public Effect{

    unsigned int _healValue;
public:
    Heal(unsigned int healValue):_healValue(healValue){};
    ~Heal(){};

    virtual void apply(CardMonster* target, Game*) override;
    virtual void apply(PlayerInGame* target, Game*) override;
    virtual bool canBeApplyOnPlayer() override {return true;}
};

/**
 * Apply a heal on a monster, the monster gain health
 *
 * @param target : the monster on which the effect will be apply
 * @param game : the game where the effect will be apply
 * @return void 
 */
void Heal::apply(CardMonster* target, Game* game) {
    target->setLife(target->getLife()+_healValue);

    if (target->getLife() > target->getMaxLife()){
    	//Target's life can't be higher than its maximum hp
    	target->setLife(target->getMaxLife());
    }
}

/**
 * Apply a heal on a player, the player gain health
 *
 * @param target : the player on which the effect will be apply
 * @param game : the game where the effect will be apply
 * @return void 
 */
void Heal::apply(PlayerInGame* target, Game* game) {
    target->addHeal(_healValue);
}

#endif	/* HEAL_HPP */
