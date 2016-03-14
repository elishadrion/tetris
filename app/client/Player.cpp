#include "Player.hpp"

Player* Player::instance;


Player::Player(std::string username, unsigned collection[MAX_CARDS], std::vector<std::string> decks,
               std::string friends[MAX_FRIENDS], unsigned victories, unsigned defeats) :
        _username(username), _decks(decks), _victories(victories), _defeats(defeats) {

    if(instance != nullptr)
        WizardLogger::error("Une instance de player existe déjà !");

    instance = this;

    for (int i = 0 ; i < MAX_CARDS ; ++i) _collection[i] = collection[i];
    for (int i = 0 ; i < MAX_FRIENDS ; ++i) _friendsList[i] = friends[i]; // TO DO
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
