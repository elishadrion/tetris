#include "CardMonster.hpp"


CardMonster::CardMonster(std::size_t id, std::string name, std::size_t energy,
    	Effect effect, bool,std::size_t life, std::size_t attack,
    	std::size_t nbrTour=0): _life(life), _attack(attack),
    	 _maxLife(life), _nbrTourPose(nbrTour),
    	 Card::Card(std::size_t id, std::string name, std::size_t energy,
    	  std::string effect, bool) { }

CardMonster::CardMonster(CardMonster& otherMonster): _life(otherMonster.getLife()),
		_attack(otherMonster.getAttack()), _maxLife(otherMonster.getMaxLife()),
		_nbrTourPose(otherMonster.getNbrTourPose()),Card::Card(otherMonster.getId(),
		 otherMonster.getName(),otherMonster.getEnergyCost(), 
		 otherMonster.getEffect(), bool) { }


void CardMonster::dealDamage(CardMonster& otherMonster){
	otherMonster.setLife(otherMonster.getLife() - this.getAttack());
}

void CardMonster::dealDamage(Player& player){
	player.setLife(player.getLife() - this.getAttack())
}

void CardMonster::incrementTour(){
	this._nbrTourPose++;
}