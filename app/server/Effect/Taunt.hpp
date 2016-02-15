#ifndef TAUNT_HPP
#define	TAUNT_HPP

#include "common/Card.hpp"
#include "server/Effect.hpp"

class Taunt : public Effect{
public:
    Taunt(){};
    ~Taunt(){};

    virtual void apply(Card* target) override {};
    virtual bool isTaunt() override {return true;};
};

#endif	/* TAUNT_HPP */