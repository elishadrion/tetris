
#include "PlayerInGame.hpp"
#include "Card.hpp"
#include "CardMonster.hpp"

/**
 * Default constructor
 */
PlayerInGame::PlayerInGame() {
    // TO DO
     _playerHeal = 20; //Player starts with 20 health points
     _energy = 0; //The current energy of the player
    _maxEnergy = 1; //Every turn the maximum energy is increased up to a maximum of 10
}

/**
 * Creates a PlayerInGame and asks to the player which Deck he would like to play with
 */
PlayerInGame::PlayerInGame(Player& player, Game* game) {
    _game = game;
    // TO DO
    // askDeck(getListDeck());
    // @tutul
}

/**
 * Gets data information from this player to send it
 *
 * @param isTurn of the current player
 */
dataIGPlayer PlayerInGame::getDataPlayer() {
    dataIGPlayer data;

    data.playerHeal = this->_playerHeal;
    data.energy = this->_energy;
    data.cardsInHand = this->_cardsInHand;
    data.cardsPlaced = this->_cardsPlaced;
    data.maxEnergy = this->_maxEnergy;
    data.limitEnergy = this-> _limitEnergy;

    return data;
}

/**
 * Sets the player deck and notify it at the game object
 *
 * @param deck The selected deck
 */
void PlayerInGame::setDeck(Deck *deck) {
    _deck = new Deck(*deck); // copy the desk
    _game->checkDeckAndStart();
}
// @tutul méthode à appeler lorsque l'on recoit un deck


/**
 * Checks if the deck of this player is defined
 *
 * @return True if the deck is defined
 */
bool PlayerInGame::isDeckDefined() {
    return _deck != nullptr;
}

/**
 * Gets random card of deck
 *
 * @return True if all is ok, False if he haven't card
 */
bool PlayerInGame::draw() {
    bool res = true;

    // TO DO
    int randomCard = _deck->pickup();
    if(randomCard != -1) {
        Card* card = CardManager::getCardById(randomCard);
        _cardsInHand.push_back(card);
    } else {
        res = false;
    }

    return res;
}



/**
 * Returns the placed cards
 */
std::vector<CardMonster*> PlayerInGame::getCardsPlaced() {
    return _cardsPlaced;
}

/**
 * Returns the cards in hand
 */
std::vector<Card*> PlayerInGame::getCardsInHand() {
    return _cardsInHand;
}


void PlayerInGame::addMaxEnergy() {
    if (_maxEnergy < _limitEnergy) {
     _maxEnergy++;
    }
}


void PlayerInGame::resetEnergy() {
    _energy = _maxEnergy;
}


unsigned PlayerInGame::nbrCardInHand() {
    return _cardsInHand.size();
}

//Checks if the player have currently enough energy to play a certain card
bool PlayerInGame::haveEnoughEnergy(Card* card) {
    return card->getEnergyCost() <= this->_energy;
}

void PlayerInGame::defausseCardPlaced(CardMonster* card) {
    auto it = std::find(_cardsPlaced.begin(), _cardsPlaced.end(), card);
    if(it != _cardsPlaced.end()) {
        _cardsPlaced.erase(it);
        _defausse.push_back(card);
    }
}

void PlayerInGame::placeCard(CardMonster* card) {
    _cardsPlaced.push_back(card);
}

void PlayerInGame::takeDamage(unsigned int damage){
    _playerHeal -= damage;
}


void PlayerInGame::getHealed(unsigned int heal){
    unsigned int maxHP = 20;
    _playerHeal += heal;
    if(_playerHeal > maxHP){
        _playerHeal = maxHP; //Can't go higher than the max
    }
}


int PlayerInGame::getHeal() {
    return _playerHeal;
}

/**
 * Add a lose to the player
 */
void PlayerInGame::addLose() {
    ++_defeats;
    // TO DO: @carlos save to JSON ?
}

/**
 * Add a win to the player
 */
void PlayerInGame::addWin() {
    ++_victories;
    // TO DO: @carlos save to JSON ?
}


/**
 * Check if the player is Dead
 */
bool PlayerInGame::isDead() {
    return _playerHeal >= 0;
}

