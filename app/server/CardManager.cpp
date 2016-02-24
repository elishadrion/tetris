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
		return nullptr;
	}
}

void CardManager::loadAllCards(){
    unsigned int id;
    std::string name;
    unsigned int energy;
    unsigned int effect;
    unsigned int life;
    unsigned int attack;

    std::ifstream ifs("card.json");//Nom + chemin fichier ou les cartes sont stockés
    json j(ifs); //Libre d'améliorer nom de variable
    //Créer un objet json a partir d'un fichier

    for (json::iterator i = j.begin(); i!=j.end(); ++i){

        id = i.value()["id"]; //Récupere la valeur a l'iterateur (toute la structure d'une carte)
        name = i.value()["name"]; //Verifier si appel entre [] fonctionne
        energy = i.value()["energie"];
        effect = i.value()["effect"];

		_listCard[id]= new Card(id,name,energy,effect,true);//Ajout des attributs
	}

	std::ifstream ifs2("cardMonster.json");//Nom + chemin fichier ou les cartes sont stockés
	json k(ifs2); //Libre d'améliorer nom de variable
	//Créer un objet json a partir d'un fichier

    for (json::iterator i = k.begin(); i!=k.end(); ++i){

        id = i.value()["id"]; //Récupere la valeur a l'iterateur (toute la structure d'une carte)
        name = i.value()["name"]; //Verifier si appel entre [] fonctionne
        energy = i.value()["energie"];
        effect = i.value()["effect"];
        life = i.value()["vie"];
        attack = i.value()["attack"];

        _listCard[id]= new CardMonster(id,name,energy,effect,true,life,attack,0); //Ajout des attributs
	}

}

Card* CardManager::chooseCardWin(){
    srand(time(NULL));

    int idAleatoire = (rand() % static_cast<unsigned>(_listCard.size())) + 1;

    return _listCard[idAleatoire];
}
