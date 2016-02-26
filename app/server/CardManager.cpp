#include "CardManager.hpp"

#include "Card.hpp" //TODO tmp patch
#include "CardMonster.hpp"

/**
 * Get the card object in cache
 *
 * @param id of the card
 * @return the card or nullptr if doesn't exist
 */

 // ATTENTION GERER ERREUR GETCARDBYID !!!!!!!!!!!

 std::map<unsigned, Card*> CardManager::_listCard;

 Card* CardManager::getCardById(const unsigned int id) {
    std::map<unsigned, Card*>::iterator it = _listCard.find(id);
    if(it != _listCard.end()) { // If card "cached"
        return _listCard[id];
    }
    else{
        WizardLogger::error("This card ID doesn't exist!");
		return nullptr;
	}
}


/**
 * Create and keep all the cards in a dictionnary witj the id as key
 *
 * @return void 
 */
void CardManager::loadAllCards(){
    unsigned int id;
    std::string name;
    unsigned int energy;
    unsigned int effect;
    unsigned int life;
    unsigned int attack;

    std::ifstream ifs("assets/cards/spells.json");//declare the file with the spells
    json spellCards(ifs); //make a json object with the file

    for (json::iterator i = spellCards.begin(); i!=spellCards.end(); ++i){

        id = i.value()["id"];
        name = i.value()["name"];
        energy = i.value()["energie"];
        effect = i.value()["effect"];

		_listCard[id]= new Card(id,name,energy,effect,true);
	}

	std::ifstream ifs2("assets/cards/monstres.json");//declare the file with the monsters
	json monsterCards(ifs2); //make a json object with the file

    for (json::iterator i = monsterCards.begin(); i!=monsterCards.end(); ++i){

        id = i.value()["id"];
        name = i.value()["name"];
        energy = i.value()["energie"];
        effect = i.value()["effect"];
        life = i.value()["vie"];
        attack = i.value()["attack"];

        _listCard[id]= new CardMonster(id,name,energy,effect,true,life,attack,0);
	}

}

/**
 * Select a random card
 *
 * @return Card* 
 */
Card* CardManager::chooseCardWin(){
    srand(time(NULL));

    int idAleatoire = (rand() % static_cast<unsigned>(_listCard.size())) + 1;

    return _listCard[idAleatoire];
}
