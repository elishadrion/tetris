
#include "Effect.hpp"

std::vector<Effect*> Effect::listEffect;

void Effect::loadAllEffect() {
    /*
    TO DO import

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
    new Draw(2);*/
}



Effect* Effect::getEffectByID(unsigned id){
    return Effect::listEffect[id];
}
