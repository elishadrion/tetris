#include "CardManager.hpp"


/**
 * Get the card object in cache
 *
 * @param id of the card
 * @return the card or nullptr if doesn't exist
 */
// Card* CardManager::getCardById(const std::size_t id) {
// 	std::map<std::size_t, Card*>::iterator it = listCard.find(id);
// 	if(it != listCard.end()) { // If card "cached"
// 		return listCard[id];
// 	}
// }

void CardManager::loadAllCards(){ //TO IMPROVE
	/*
	std::size_t id;
	string name;
	std::size_t energy;
	std::size_t	effect;
	std::size_t	life;
	std::size_t attack;
	bool cardMonster;

	std::ifstream ifs("card.json");//Nom + chemin fichier ou les cartes sont stockés
	json j(ifs); //Libre d'améliorer nom de variable
	//Créer un objet json a partir d'un fichier

	for (json::iterator i = j.begin(); i!=j.end(); ++i){

		id = i.value()["id"]; //Récupere la valeur a l'iterateur (toute la structure d'une carte)
		name = i.value()["name"]; //Verifier si appel entre [] fonctionne
		energy = i.value()["energie"];
		effect = i.value()["effect"];

		cardMonster = i.value()["monster"];
		//Ajout d'un booléen dans le json discernant monstre et sort
		//A proposer au groupe

		if (cardMonster){

			life = i.value()["vie"];
			attack = i.value()["attack"];
			listCard[id]= new CardMonster(); //Ajout des attributs
		}

		else{
		
			listCard[id]= new Card();//Ajout des attributs
		}
	}
	*/
}
