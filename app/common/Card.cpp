
#include "Card.hpp"

/**
 * Constructor
 *
 * @param id of the card
 * @param name of the card
 * @param energy of the card
 * @param heal of the card
 * @param effect name of the specific effect
 * @param save True if save in cache
 */
Card::Card(std::size_t id, std::string name, std::size_t energy, std::size_t heal,
        std::string effect, bool save = true) {

    _id = id;
    _name = name;
    _energyCost = energy;
    _heal = heal;
    _effect = Effect.getEffect(effect);

    if(save) {
        listCard.insert(std::pair<std::size_t,Card>(id,this));
    }
}


/**
 * Copy contructor
 *
 * @param card original
 */
Card::Card(Card card) {
    _id = card._id;
    _name = card._name;
    _energyCost = card._energyCost;
    _heal = card._heal;
    _effect = card._effect;
}


/**
 * Get the card object
 *
 * @param id of the card
 * @return the card
 */
Card Card::getCard(std::size_t id) {
    std::map<std::size_t, Card>::iterator it = listCard.find(id);
    if(it != listCard.end()) { // If card "cached"
        return listCard[id];
    }

    return CardManager.loadCard(id);
}


/**
 * Expilcit copy of this card
 *
 * @return the new card
 */
Card Card::copy() {
    return new Card(this);
}

/**
 * Event when we place a card
 */
void Card::placeCard() {
    Listener.onPlaceCard(this);
}



