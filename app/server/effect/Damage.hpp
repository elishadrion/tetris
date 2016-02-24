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

void Damage::apply(CardMonster* target, Game* game){
    target->setLife(target->getLife()-_damageValue);
}

void Damage::apply(PlayerInGame* target, Game* game){
    target->takeDamage(_damageValue);
}

#endif	/* DAMAGE_HPP */
