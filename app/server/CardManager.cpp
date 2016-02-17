#include "CardManager.hpp"


/**
 * Get the card object in cache
 *
 * @param id of the card
 * @return the card or nullptr if doesn't exist
 */
Card* CardManager::getCardById(const std::size_t id) {
	std::map<std::size_t, Card*>::iterator it = listCard.find(id);
	if(it != listCard.end()) { // If card "cached"
		return listCard[id];
	}
}

void CardManager::loadAllCards(){
	
}