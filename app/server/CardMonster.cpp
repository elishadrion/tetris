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
void CardMonster::dealDamage(CardMonster* otherMonster){

    // Set life adverse monster
    unsigned advLife = 0;
    if(otherMonster->getLife() > getAttack()) {
        advLife = otherMonster->getLife()-getAttack();
    }
    otherMonster->setLife(advLife);

    // Set us life
    unsigned life = 0;
    if(getLife() > getAttack()) {
        life = getLife() - getAttack();
    }
    setLife(life);

}

/**
 * The monster attack a player
 *
 * @param player
 * @return void
 */
void CardMonster::dealDamage(PlayerInGame& player){
    player.takeDamage(getAttack());

    // Set us life
    unsigned life = 0;
    if(getLife() > getAttack()) {
        life = getLife() - getAttack();
    }
    setLife(life);
}

/**
 * Increment the tour of the monster
 */
void CardMonster::incrementTour(){
    ++_nbrTourPose;
}

/**
 * Check if the monster is dead
 *
 * @return true if the monster is dead
 */
bool CardMonster::isDead() {
    return _life <= 0;
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
