#include "GameManager.hpp"

GameManager* GameManager::_instance;


GameManager* GameManager::getInstance() {
    return _instance;
}

/**
 * Set deck and send information to the server
 *
 * @param deckName the deck name
 */
void GameManager::setDeck(std::string deckName) {
    if(_deckName == "") {
        WizardLogger::info("Envoie du nom du deck: " + deckName);

        _deckName = deckName;
        PacketManager::sendSelectedDeck(_deckName.c_str());

    } else {
        WizardLogger::warning("Le deck à déjà été définit");
    }
}



