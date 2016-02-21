#include "CardMonster.hpp"


CardMonster::CardMonster(std::size_t id, std::string name, std::size_t energy,
    	int effect, bool aBool,std::size_t life, std::size_t attack,
    	std::size_t nbrTour): _life(life), _attack(attack),
    	 _maxLife(life), _nbrTourPose(nbrTour),
    	 Card::Card(id, name, energy, effect, aBool) { }

CardMonster::CardMonster(CardMonster& otherMonster): _life(otherMonster.getLife()),
		_attack(otherMonster.getAttack()), _maxLife(otherMonster.getMaxLife()),
		_nbrTourPose(otherMonster.getNbrTourPose()),Card::Card(otherMonster.getId(),
		 otherMonster.getName(),otherMonster.getEnergyCost(),
		 otherMonster.getEffectID(), false) { }


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
