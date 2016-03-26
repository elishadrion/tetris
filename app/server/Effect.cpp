
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

Effect::Effect() {
    _listEffect.push_back(this);
    _id = (static_cast<int>(_listEffect.size())-1);
}

/**
 * Create and save all the effects in a vector 
 *
 * @return void 
 */
void Effect::loadAllEffect() {

    new Taunt(); // 0
    new Heal(1); // 1
    new Heal(2); // 2
    new Heal(3); // 3
    new Damage(1); // 4
    new Damage(2); // 5
    new Damage(3); // 6
    new LifeBlessing(1); // 7
    new LifeBlessing(2); // 8
    new AttackBlessing(1); // 9
    new AttackBlessing(2); // 10
    new LifeCurse(1); // 11
    new LifeCurse(2); // 12
    new AttackCurse(1); // 13
    new AttackCurse(2); // 14
    new Draw(1); // 15
    new Draw(2); // 16
}

/**
 * Get the effect that match with the id 
 *
 * @param id : the id of an effect
 * @return Effect* 
 */
Effect* Effect::getEffectByID(unsigned id){
    return Effect::_listEffect[id];
}
