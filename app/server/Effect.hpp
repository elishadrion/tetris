#ifndef EFFECT_HPP
#define	EFFECT_HPP

#include "common/Card.hpp"
#include <vector>

class Effect { //Abstract class
	static std::vector<Effect*> listEffect;
public:
    virtual Effect(){ 
    //Attention, vérifier si classes filles appellent cosntructeur parent
    	listEffect.push_back(this);
    };
    virtual ~Effect(){};

    static void loadAllEffect();
    static Effect* getEffectByID(std::size_t);
    virtual void apply(Card*) = 0;
    virtual bool isTaunt(){return false;};
};

void Effect::loadAllEffect(){
	new Taunt();
	new Heal(1);
	new Heal(2);
	new Heal(3);
	new Damage(1);
	new Damage(2);
	new Damage(3);
	new LifeBlessing(1);
	new LifeBlessing(2);
	new AttackBlessing(1);
	new AttackBlessing(2);
	new LifeCurse(1);
	new LifeCurse(2);
	new AttackCurse(1);
	new AttackCurse(2);
	new Draw(1);
	new Draw(2);
}

Effect* Effect::getEffectByID(std::size_t id){
	return listEffect[id];
}

#endif	/* EFFECT_HPP */