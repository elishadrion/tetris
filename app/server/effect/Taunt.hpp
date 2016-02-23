#ifndef TAUNT_HPP
#define TAUNT_HPP

class CardMonster;
#include "server/Effect.hpp"

class Taunt : public Effect{
public:
    Taunt(){};
    ~Taunt(){};

    virtual void apply(CardMonster* target) override {};
    virtual bool isTaunt() override {return true;};
};

#endif  /* TAUNT_HPP */
