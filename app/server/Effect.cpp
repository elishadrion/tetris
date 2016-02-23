
#include "Effect.hpp"
#include "CardMonster.hpp"
#include "effect/Taunt.hpp"
#include "effect/Heal.hpp"
#include "effect/Damage.hpp"
#include "effect/LifeBlessing.hpp"
#include "effect/LifeCurse.hpp"
#include "effect/AttackBlessing.hpp"
#include "effect/AttackCurse.hpp"
#include "effect/Draw.hpp"

std::vector<Effect*> Effect::_listEffect;

void Effect::loadAllEffect() {

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

Effect* Effect::getEffectByID(unsigned id){
    return Effect::_listEffect[id];
}
