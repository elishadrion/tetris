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
        Effect effect, bool save = true):
        _id(id), _name(name), _energyCost(energy), _effect(effect) {

    if(save) {
        listCard.insert(std::pair<std::size_t,Card*>(id,this));
    }
}


/**
 * Copy contructor
 *
 * @param card original
 */
Card::Card(Card& card) : _id(card.getId()), _name(card.getName()), _energyCost(card.getEnergyCost()),
     _effect(card.getEffect()) { }


void Card::applyEffect(Card& card){
    this.Effect::apply(Card& card);
}
