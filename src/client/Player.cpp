#include "Player.hpp"

Player* Player::instance;


Player::Player(std::string username, unsigned victories, unsigned defeats) :
        _username(username), _victories(victories), _defeats(defeats) {

    if(instance != nullptr) {
        WizardLogger::error("Une instance de player existe déjà !");
    } else {
        instance = this;
    }
}

