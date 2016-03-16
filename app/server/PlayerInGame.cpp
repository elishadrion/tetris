
#include "PlayerInGame.hpp"
#include "Card.hpp"
#include "CardMonster.hpp"

/**
 * Creates a PlayerInGame and asks to the player which Deck he would like to play with
 */
PlayerInGame::PlayerInGame(const Player& player, Game* game): Player(player),
    _deck(nullptr), _game(game) {

    WizardLogger::info("Création d'un PlayerInGame: " + player.getName() + " > " + this->getName());

    _playerHeal = MAX_LIFE; //Player starts with 20 health points
     _energy = 0; //The current energy of the player
    _maxEnergy = 1; //Every turn the maximum energy is increased up to a maximum of 10
    std::vector<Card*> _cardsInHand(0);
    std::vector<Card*> _defausse(0);
    std::vector<CardMonster*> _cardsPlaced(0);

    _playerConnect->setPlayerInGame(this);

    // Ask to the palyer his deck
    PacketManager::askDeck(this);
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
    data.limitEnergy = this->_limitEnergy;

    return data;
}

/**
 * Sets the player deck and notifies it at the game object
 *
 * @param deck The selected deck
 */
void PlayerInGame::setDeck(std::string deck) {
    Deck* ptrDeck = nullptr;
    int i = 0;
    while(i < _decks.size() && ptrDeck == nullptr) {
        Deck* currentDeck = _decks[i];
        if(currentDeck->getName() == deck) {
            ptrDeck = currentDeck;
        }
        ++i;
    }

    if(ptrDeck != nullptr) {
        _deck = new Deck(*ptrDeck); // copy the deck
        WizardLogger::info("Choix du deck: " + _deck->getName());
        _game->checkDeckAndStart();
    } else {
        WizardLogger::warning("Le deck: " + deck + " n'a été pas trouvé");
    }
}


/**
 * Checks if the deck of this player is defined
 *
 * @return True if the deck is defined
 */
bool PlayerInGame::isDeckDefined() {
    return _deck != nullptr;
}


/**
 * Gets random card of deck and place it in
 * his hand !
 *
 * @return the card or nullptr
 */
Card* PlayerInGame::draw() {
    Card* res = nullptr;

    Card* randomCard = _deck->pickup();
    if(randomCard != nullptr) {
        _cardsInHand.push_back(randomCard);
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


/**
 * Permet de remettre l'énergie au maximum
 *
 * @return la nouvelle valeur d'énergie
 */
int PlayerInGame::resetEnergy() {
    _energy = _maxEnergy;
    return _energy;
}


unsigned PlayerInGame::nbrCardInHand() {
    return static_cast<unsigned>(_cardsInHand.size());
}

//Checks if the player have currently enough energy to play a certain card
bool PlayerInGame::haveEnoughEnergy(Card* card) {
    return this->_energy > 0 &&
        card->getEnergyCost() <= static_cast<unsigned>(this->_energy);
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
    const int maxHP = 20;
    _playerHeal += heal;
    if(_playerHeal > maxHP){
        _playerHeal = maxHP; //Can't go higher than the max
    }
}


int PlayerInGame::getHeal() {
    return _playerHeal;
}

/**
 * Adds a defeat to the player
 */
void PlayerInGame::addDefeat() {
    ++_defeats;
}

/**
 * Adds a win to the player
 */
void PlayerInGame::addWin() {
    ++_victories;
}


/**
 * Checks if the player is Dead
 */
bool PlayerInGame::isDead() {
    return _playerHeal <= 0;
}

PlayerInGame::~PlayerInGame() {
    _playerConnect->removePlayerInGame(this);
}
