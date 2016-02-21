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
Card::Card(std::size_t id, std::string name, std::size_t energy,
        int effect, bool save = true):
        _id(id), _name(name), _energyCost(energy), _effect(effect) {

    if(save) {
        //TODO tmp patch listCard.insert(std::pair<std::size_t,Card*>(id,this));
    }
}


/**
 * Copy contructor
 *
 * @param card original
 */
Card::Card(Card& card) : _id(card.getId()), _name(card.getName()), _energyCost(card.getEnergyCost()),
      _effect(card.getEffectID()) { }


void Card::applyEffect(CardMonster& cardmonster){
    if (this->gotEffect()){
        Effect::getEffectByID(this->getEffectID())->apply(&cardmonster);
    }
}

void Card::applyEffect(PlayerInGame& player){
    if (this->gotEffect()){
        //Effect::getEffectByID(this->getEffectID())->apply(&player);
    }
}

bool Card::gotEffect(){
	if (this->getEffectID() == -1){
		return false;
	}
	else {
		return true;
	}
}

Card::~Card() {};
