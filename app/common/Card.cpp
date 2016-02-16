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
        /*Effect effect, //TODO tmp patch */ bool save = true):
        _id(id), _name(name), _energyCost(energy) { //TODO , tmp patch _effect(effect) {

    if(save) {
        //TODO tmp patch listCard.insert(std::pair<std::size_t,Card*>(id,this));
    }
}


/**
 * Copy contructor
 *
 * @param card original
 */
Card::Card(Card& card) : _id(card.getId()), _name(card.getName()), _energyCost(card.getEnergyCost())
     {} //TODO , tmp patch_effect(card.getEffect()) { }


void Card::applyEffect(Card& card){
    //TODO tmp patch this.Effect::apply(Card& card);
}

Card::~Card() {};
