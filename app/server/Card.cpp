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
Card::Card(unsigned int id, std::string name, unsigned int energy, int effect):
        _id(id), _name(name), _energyCost(energy) {

    if(effect != -1) {
        _effect = Effect::getEffectByID(effect);
    }
}

/**
 * Apply the effect on a monster
 *
 * @param the monster targeted
 * @param the game where the effect will be apply
 */
void Card::applyEffect(CardMonster* cardmonster, Game* game){
    if(this->gotEffect() && this->canBeApplyOnCard()){
        _effect->apply(cardmonster, game);
    }
}

/**
 * Apply the effect on a player
 *
 * @param the player targeted
 * @param the game where the effect will be apply
 */
void Card::applyEffect(PlayerInGame* player, Game* game){
    if (this->gotEffect() && this->canBeApplyOnPlayer()){
        _effect->apply(player, game);
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


/**
 * Clone the current card
 *
 * @return the new card
 */
Card* Card::clone() {
    return new Card(*this);
}


Card::~Card() {}
