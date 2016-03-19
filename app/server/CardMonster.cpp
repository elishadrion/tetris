#include "CardMonster.hpp"

/**
 * Constructor
 *
 * @param id of the card
 * @param name of the card
 * @param energy of the card
 * @param effect id of the specific effect
 * @param save True if save in cache
 * @param life of the card
 * @param attack of the card
 * @param number of tour that the card is placed
 */
CardMonster::CardMonster(unsigned int id, std::string name, unsigned int energy,
    	int effect, bool aBool,unsigned int life, unsigned int attack,
    	unsigned int nbrTour): Card::Card(id, name, energy, effect, aBool),
		_life(life), _attack(attack), _maxLife(life), _nbrTourPose(nbrTour),
        _taunt(false) { }

CardMonster::CardMonster(CardMonster& otherMonster): Card(otherMonster),
    _life(otherMonster._life), _attack(otherMonster._attack),
    _maxLife(otherMonster._maxLife), _nbrTourPose(otherMonster._nbrTourPose),
    _taunt(otherMonster._taunt) { }


/**
 * The monster attack an other monster
 *
 * @param card (other monster)
 * @return void
 */
void CardMonster::dealDamage(CardMonster& otherMonster){
	otherMonster.setLife(otherMonster.getLife() - this->getAttack());
}

/**
 * The monster attack a player
 *
 * @param player
 * @return void
 */
void CardMonster::dealDamage(PlayerInGame& player){
	player.takeDamage(this->getAttack());
}

/**
 * Increment the tour of the monster
 *
 * @return void
 */
void CardMonster::incrementTour(){
	this->_nbrTourPose++;
}

/**
 * Check if the monster is dead
 *
 * @return true if the monster is dead
 */
bool CardMonster::isDead() {
	if (this->_life > 0){
		return false;
	}
	else{
		return true;
	}
}


/**
 * Clone the current card
 *
 * @return the new card
 */
Card* CardMonster::clone() {
    return new CardMonster(*this);
}


CardMonster::~CardMonster() { }
