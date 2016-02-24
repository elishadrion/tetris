#ifndef TAUNT_HPP
#define TAUNT_HPP

class CardMonster;
#include "server/Effect.hpp"
class Game;

class Taunt : public Effect{
public:
    Taunt(){};
    ~Taunt(){};
    virtual bool isTaunt() override {return true;};
    virtual void apply(CardMonster*, Game*) override;
};

void Taunt::apply(CardMonster* target, Game* game){
	target->setTaunt(true);
}


#endif  /* TAUNT_HPP */
