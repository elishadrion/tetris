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

    /*
    std::ifstream playersFile;
    try {
	playersFile.open(PLAYERS_DB);
    } catch (std::ios_base::failure &fail) {
	WizardLogger::warning("LOADING USERS FAILED");
	return;
    }

    std::string info_str((std::istreambuf_iterator<char>(playersFile)),
			 std::istreambuf_iterator<char>());
    nlohmann::json db = nlohmann::json::parse(info_str);

    for (size_t i = 0 ; i < db.size(); ++i) {
	nlohmann::json player_info = db[i];
	_players.push_back(new Player(player_info));
    }

    playersFile.close();
    */

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


    //std::ifstream ifs("server/assets/cards/spells.json");//declare the file with the spells
    //json spellCards(ifs); //make a json object with the file

    for (json::iterator i = spellCards.begin(); i!=spellCards.end(); ++i){

        id = i.value()["id"];
        WizardLogger::info("Chargement de la carte sort: " + std::to_string(id));
        name = i.value()["name"];
        energy = i.value()["energie"];
        effect = i.value()["effect"];

		_listCard[id]= new Card(id,name,energy,effect,true);
	}

	//std::ifstream ifs2("server/assets/cards/monstres.json");//declare the file with the monsters
	//json monsterCards(ifs2); //make a json object with the file


    std::ifstream cardFile;
    try {
	  cardFile.open("server/assets/cards/monstres.json");
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
