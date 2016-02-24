#include "CardMonster.hpp"


CardMonster::CardMonster(unsigned int id, std::string name, unsigned int energy,
    	int effect, bool aBool,unsigned int life, unsigned int attack,
    	unsigned int nbrTour): Card::Card(id, name, energy, effect, aBool),
		_life(life), _attack(attack), _maxLife(life), _nbrTourPose(nbrTour)
    	{ }

CardMonster::CardMonster(CardMonster& otherMonster): Card(otherMonster),
    _life(otherMonster._life), _attack(otherMonster._attack),
    _maxLife(otherMonster._maxLife), _nbrTourPose(otherMonster._nbrTourPose) { }


void CardMonster::dealDamage(CardMonster& otherMonster){
	otherMonster.setLife(otherMonster.getLife() - this->getAttack());
}

void CardMonster::dealDamage(PlayerInGame& player){
	player.takeDamage(this->getAttack());
}

void CardMonster::incrementTour(){
	this->_nbrTourPose++;
}

bool CardMonster::isDead() {
	if (this->_life > 0){
		return false;
	}
	else{
		return true;
	}
}

CardMonster::~CardMonster() { }
