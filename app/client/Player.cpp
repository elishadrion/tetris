#include "Player.hpp"

Player* Player::instance;


Player::Player(std::string username, unsigned collection[MAX_CARDS], int decks[MAX_DECKS],
               std::string friends[MAX_FRIENDS], unsigned victories, unsigned defeats) :
        _username(username), _victories(victories), _defeats(defeats) {

    if(instance != nullptr)
        WizardLogger::error("Une instance de player existe déjà !");

    instance = this;

    for (int i = 0 ; i < MAX_CARDS ; ++i) _collection[i] = collection[i];
    for (int i = 0 ; i < MAX_DECKS ; ++i) _decks[i] = decks[i];
    for (int i = 0 ; i < MAX_FRIENDS ; ++i) _friendsList[i] = friends[i];
}

void Player::addDeck(int ID) {
    for (int i = 0 ; i < MAX_DECKS ; ++i) {
        if (_decks[i] == -1) {
            _decks[i] = ID;
        }
    }
}

void Player::removeDeck(int ID) {
    for (int i = 0 ; i < MAX_DECKS ; ++i){
        if (_decks[i] == ID) {
            _decks[i] = -1;
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
