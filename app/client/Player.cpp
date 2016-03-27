#include "Player.hpp"

Player* Player::instance;


Player::Player(std::string username, unsigned collection[MAX_CARDS], std::vector<std::string> decks,
               std::string friends[MAX_FRIENDS], unsigned victories, unsigned defeats) :
        _username(username), _decks(decks), _victories(victories), _defeats(defeats) {

    if(instance != nullptr) {
        WizardLogger::error("Une instance de player existe déjà !");
    } else {
        instance = this;

        for (int i = 0 ; i < MAX_CARDS ; ++i) _collection[i] = collection[i];
        for (int i = 0 ; i < MAX_FRIENDS ; ++i) {
	        _friendsList[i] = friends[i];
	        std::cout << friends[i] << "\n";
	    }
    }
}

Error Player::addDeck(std::string name) {
    Error res = Error::MaxDeck;

    if(_decks.size() < 10) {
        _decks.push_back(name);
        res = Error::NoError;
    }

    return res;
}

Error Player::removeDeck(std::string name) {
    Error res = Error::MustOneDeckMin;

    if(_decks.size() > 1) {
        res = Error::DeckNotFound;

        std::vector<std::string>::iterator it = std::find(_decks.begin(), _decks.end(), name);
        if(it != _decks.end()) {
            _decks.erase(it);
            res = Error::NoError;
        }
    }

}

void Player::addFriend(std::string pseudo) {
    for (int i = 0 ; i < MAX_FRIENDS ; ++i) {
        if (_friendsList[i] == "") {
            _friendsList[i] = pseudo;
        }
    }
}
void Player::removeFriend(std::string pseudo) {
    for (int i = 0 ; i < MAX_FRIENDS ; ++i)  {
        if (_friendsList[i] == pseudo) {
            _friendsList[i] = "";
        }
    }
}

void Player::addDeckCard(std::vector<unsigned> listCardId) {
    if(listCardId.size() == DECK_SIZE) {
        for(int i = 0; i < DECK_SIZE; ++i) {
            _listCardDeck.push_back(listCardId[i]);
        }
    } else {
        WizardLogger::warning("Pour enregistrer un deck il doit avoir la bonne taille");
    }
}

std::vector<unsigned> Player::getCardDeck(std::string nomDeck) {
    std::vector<unsigned> res;

    unsigned i = 0;
    bool found = false;
    while(!found && i < _decks.size()) {
        found = _decks[i] == nomDeck;
        ++i;
    }

    if(found) {
        --i; // adjust index
        unsigned posActuel = DECK_SIZE*i;
        for(unsigned nbrCard = 0; nbrCard < DECK_SIZE; ++nbrCard) {
            res.push_back(_listCardDeck[posActuel+nbrCard]);
        }

    } else {
        WizardLogger::warning("Deck introuvable");
    }

    return res;
}

void Player::loadDeckCard() {
    /* Lock */
    pthread_mutex_lock(&wizardDisplay->packetStackMutex);

    // Packet manager
    WizardLogger::info("Récupération des cartes du deck");
    PacketManager::reqGetDeck();

    /* Wait for result */
    pthread_cond_wait(&wizardDisplay->packetStackCond, &wizardDisplay->packetStackMutex);

    /* Unlock */
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);
}


////////////////////// IN GAME //////////////////////
//void Player::setDeck(std::string deckName) {
//    if(_deckName == "") {
//        WizardLogger::info("Envoie du nom du deck: " + deckName);

//        _deckName = deckName;
//        PacketManager::sendSelectedDeck(_deckName.c_str());

//    } else {
//        WizardLogger::warning("Le deck à déjà été définit");
//    }
//}
