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
        _id(id), _name(name), _energyCost(energy) {

    if(effect != -1) {
        _effect = Effect::getEffectByID(effect);
    }

    if(save) {
        //TODO tmp patch listCard.insert(std::pair<unsigned int,Card*>(id,this));
    }
}

/**
 * Apply the effect on a monster
 *
 * @param the monster targeted
 * @param the game where the effect will be apply
 * @return void
 */
void Card::applyEffect(CardMonster& cardmonster, Game& game){
    if(this->gotEffect() and this->canBeApplyOnCard()){
        _effect->apply(&cardmonster, &game);
    }
}

/**
 * Apply the effect on a player
 *
 * @param the player targeted
 * @param the game where the effect will be apply
 * @return void
 */
void Card::applyEffect(PlayerInGame& player, Game& game){
    if (this->gotEffect() and this->canBeApplyOnPlayer()){
        _effect->apply(&player, &game );
    }
}

/**
 * Check if the card got an effect
 *
 * @return true if yes, false if not
 */
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

/**
 * Check if the effect can be apply on a player
 *
 * @return true if yes, false if not
 */
bool Card::canBeApplyOnPlayer(){
    return _effect->canBeApplyOnPlayer();
}

/**
 * Check if the effect can be apply on a player
 *
 * @return true if yes, false if not
 */
bool Card::canBeApplyOnCard(){
    return _effect->canBeApplyOnCard();
}

Card::~Card() {}
