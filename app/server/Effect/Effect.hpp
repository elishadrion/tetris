#ifndef EFFECT_HPP
#define	EFFECT_HPP

#include "common/Card.hpp"

class Effect {
public:
    Effect(){};
    ~Effect(){};

    virtual void apply(Card*) = 0;
    virtual bool isTaunt(){return false;};
};

#endif	/* EFFECT_HPP */