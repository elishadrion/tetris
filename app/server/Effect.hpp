/*
Version provisoire, il faut séparer les classes etc.
*/

#ifndef EFFECT_HPP
#define	EFFECT_HPP

#include "Card.hpp"
#include "CardMonster.hpp"
#include "Game.hpp"

class Effect {
public:
    Effect(){};

    virtual void apply(Card)=0;
    virtual bool isTaunt(return false);
};

/////////////////TAUNT//////////////////////

class Taunt : virtual public Effect{
public:
    Taunt(){};

    virtual void apply(Card target){} override;
    virtual bool isTaunt(return true) override;
};

/////////////////HEAL///////////////////////

class Heal : virtual public Effect{

    std::size_t _healValue;
public:
    Heal(std::size_t healValue):_healValue(healValue){};

    virtual void apply(Card) override;
};

void Heal::apply(Card target){
    target.setLife(target.getLife()+_healValue);
}

/////////////////DAMAGE/////////////////////

class Damage : virtual public Effect{

    std::size_t _damageValue;
public:
    Damage(std::size_t damageValue):_damageValue(damageValue){};

    virtual void apply(Card) override;
};

void Damage::apply(Card target){
    target.setLife(target.getLife()-_damageValue);
}

/////////////////LIFEBLESSING/////////////////////

class LifeBlessing : virtual public Effect{

    std::size_t _lifeValue;
public:
    LifeBlessing(std::size_t lifeValue):_lifeValue(lifeValue){};

    virtual void apply(Card) override;
};

void LifeBlessing::apply(Card target){
    target.setMaxLife(target.getMaxLife()+_lifeValue);
    target.setLife(target.getLife()+_lifeValue);
}

/////////////////ATTACKBLESSING/////////////////////

class AttackBlessing : virtual public Effect{

    std::size_t _attackValue;
public:
    AttackBlessing(std::size_t attackValue):_attackValue(attackValue){};

    virtual void apply(Card) override;
};

void AttackBlessing::apply(Card target){
    target.setAttack(target.getAttack()+_attackValue);
}

/////////////////LIFECURSE/////////////////////

class LifeCurse : virtual public Effect{

    std::size_t _lifeValue;
public:
    LifeCurse(std::size_t lifeValue):_lifeValue(lifeValue){};

    virtual void apply(Card) override;
};

void LifeCurse::apply(Card target){
    target.setMaxLife(_lifeValue);
    if (target.getLife() > _lifeValue ){
        target.setLife(_lifeValue);
    }
}

/////////////////ATTACKCURSE/////////////////////

class AttackCurse : virtual public Effect{

    std::size_t _attackValue;
public:
    AttackCurse(std::size_t attackValue):_attackValue(attackValue){};

    virtual void apply(Card) override;
};

void AttackCurse::apply(Card target){
    target.setAttack(_attackValue);
}

/////////////////DRAW/////////////////////

class Draw : virtual public Effect{

    std::size_t _nDraw;
public:
    Draw(std::size_t nDraw):_nDraw(nDraw){};

    //Soit on suit le meme principe que Taunt avec une fonction isDraw qui est géré dans le jeu
    //Soit on peut peut-etre include Game (la fonction qui pioche)
    //et apply lancerait la fonction comme ci-dessous

    virtual void apply(Card) override;
};

void Draw::apply(Card target){
    for (std::size_t i=0; i<_nDraw; i++){
        Game::draw();
    }
}

#endif	/* EFFECT_HPP */