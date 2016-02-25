#ifndef DAMAGE_HPP
#define	DAMAGE_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
#include "server/PlayerInGame.hpp"
class Game;

class Damage : public Effect{

    unsigned int _damageValue;
public:
    Damage(unsigned int damageValue):_damageValue(damageValue){};
    ~Damage(){};

    virtual void apply(CardMonster*, Game*) override;
    virtual void apply(PlayerInGame*, Game*) override;
    virtual bool canBeApplyOnPlayer() override {return true;};
};

/**
 * Apply damage on a monster, the monster loose health
 *
 * @param target : the monster on which the effect will be apply
 * @param game : the game where the effect will be apply
 * @return void 
 */
void Damage::apply(CardMonster* target, Game* game){
    target->setLife(target->getLife()-_damageValue);
}

/**
 * Apply damage on a player, the player loose health
 *
 * @param target : the player on which the effect will be apply
 * @param game : the game where the effect will be apply
 * @return void 
 */
void Damage::apply(PlayerInGame* target, Game* game){
    target->takeDamage(_damageValue);
}

#endif	/* DAMAGE_HPP */
