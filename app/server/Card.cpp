#include "Card.hpp"

/**
 * Constructor
 *
 * @param id of the card
 * @param name of the card
 * @param energy of the card
 * @param effect name of the specific effect
 * @param save True if save in cache
 */
Card::Card(unsigned int id, std::string name, unsigned int energy,
        int effect, bool save = true):
        _id(id), _name(name), _energyCost(energy),
        _effect(Effect::getEffectByID(effect)), _taunt(false) {

    if(effect != -1) {
        _effect = Effect::getEffectByID(effect);

        _taunt = _effect->isTaunt();
    }

    if(save) {
        //TODO tmp patch listCard.insert(std::pair<unsigned int,Card*>(id,this));
    }
}


void Card::applyEffect(CardMonster& cardmonster){
    if (this->gotEffect() and this->canBeApplyOnCard()){
        _effect->apply(&cardmonster);
    }
}

void Card::applyEffect(PlayerInGame& player){
    if (this->gotEffect() and this->canBeApplyOnPlayer()){
        _effect->apply(&player);
    }
}

bool Card::gotEffect(){
    return this->getEffectID() != -1;
}

/**
 * Return the effect id
 *
 * @return -1 if no effect or the effect id
 */
int Card::getEffectID() {
    int res = -1;
    if(_effect != nullptr) {
        res = _effect->getId();
    }

    return res;
}


bool Card::canBeApplyOnPlayer(){
    return _effect->canBeApplyOnPlayer();
}

bool Card::canBeApplyOnCard(){
    return _effect->canBeApplyOnCard();
}

Card::~Card() {}
