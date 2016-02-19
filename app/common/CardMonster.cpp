#include "CardMonster.hpp"


CardMonster::CardMonster(std::size_t id, std::string name, std::size_t energy,
    	/* Effect effect, //TODO tmp patch */ bool aBool,std::size_t life, std::size_t attack,
    	std::size_t nbrTour): _life(life), _attack(attack),
    	 _maxLife(life), _nbrTourPose(nbrTour),
    	 Card::Card(id, name, energy,
    	  /* //TODO tmp patch std::string effect, */ aBool) { }

CardMonster::CardMonster(CardMonster& otherMonster): _life(otherMonster.getLife()),
		_attack(otherMonster.getAttack()), _maxLife(otherMonster.getMaxLife()),
		_nbrTourPose(otherMonster.getNbrTourPose()),Card::Card(otherMonster.getId(),
		 otherMonster.getName(),otherMonster.getEnergyCost(),
		 /* //TODO tmp patch otherMonster.getEffect(), bool */ false) { }


void CardMonster::dealDamage(CardMonster& otherMonster){
	otherMonster.setLife(otherMonster.getLife() - this->getAttack());
}

void CardMonster::dealDamage(Player& player){
	//TODO tmp patch player.setLife(player.getLife() - this->getAttack())
}

void CardMonster::incrementTour(){
	this->_nbrTourPose++;
}

bool CardMonster::isDeath() {
    return this->_life >= 0;
}
