#include "CardManager.hpp"

#include "Card.hpp" //TODO tmp patch
#include "CardMonster.hpp"

// ATTENTION GERER ERREUR GETCARDBYID !!!!!!!!!!!

std::map<unsigned, Card*> CardManager::_listCard;

/**
 * Get the card object in cache
 *
 * @param id of the card
 * @return the card or nullptr if doesn't exist
 */
Card* CardManager::getCardById(const unsigned int id) {
    std::map<unsigned, Card*>::iterator it = _listCard.find(id);
    if(it != _listCard.end()) { // If card "cached"
        return _listCard[id];
    }
    else{
        WizardLogger::error("This card ID " + std::to_string(id) + " doesn't exist!");
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

    ////// Card Spell //////
    std::ifstream spellFile;
    try {
	  spellFile.open("server/assets/cards/spells.json");
    } catch (std::ios_base::failure &fail) {
	  WizardLogger::warning("LOADING SPELL FAILED");
	  return;
    }

    std::string info_spell_str((std::istreambuf_iterator<char>(spellFile)),
			 std::istreambuf_iterator<char>());
    nlohmann::json spellCards = nlohmann::json::parse(info_spell_str);

    for (json::iterator i = spellCards.begin(); i!=spellCards.end(); ++i){
        id = i.value()["id"];
        WizardLogger::info("Chargement de la carte sort: " + std::to_string(id));
        name = i.value()["name"];
        energy = i.value()["energie"];
        effect = i.value()["effect"];
        // Enregistrer la carte
        _listCard[id]= new Card(id,name,energy,effect,true);
	}
	spellFile.close();


    ////// Card Monster //////
    std::ifstream cardFile;
    try {
	  cardFile.open("server/assets/cards/monsters.json");
    } catch (std::ios_base::failure &fail) {
	  WizardLogger::warning("LOADING CARD FAILED");
	  return;
    }

    std::string info_monster_str((std::istreambuf_iterator<char>(cardFile)),
			 std::istreambuf_iterator<char>());
    nlohmann::json monsterCards = nlohmann::json::parse(info_monster_str);

    for (json::iterator i = monsterCards.begin(); i!=monsterCards.end(); ++i){
        id = i.value()["id"];
        WizardLogger::info("Chargement de la carte monstre: " + std::to_string(id));
        name = i.value()["name"];
        energy = i.value()["energie"];
        effect = i.value()["effect"];
        life = i.value()["vie"];
        attack = i.value()["attack"];
        // Enregistrer la carte
        _listCard[id]= new CardMonster(id,name,energy,effect,true,life,attack,0);
	}

	cardFile.close();

}

/**
 * Select a random card
 *
 * @return Card*
 */
Card* CardManager::chooseCardWin(){
    srand(time(NULL));

    int idAleatoire = (rand() % static_cast<unsigned>(_listCard.size())) + 1;
    //TODO check if card already exist for the player (max two same cards)
    return _listCard[idAleatoire];
}

unsigned CardManager::getNbrCard() {
    return static_cast<unsigned>(_listCard.size());
}

