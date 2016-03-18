
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
    CardMonster _cardsPlaced[MAX_POSED_CARD];

    _playerConnect->setPlayerInGame(this);

    // Ask to the palyer his deck
    PacketManager::askDeck(this);
}


///////////// Getters /////////////

/**
 * Returns the placed cards
 * @return the vector of card placed
 */
CardMonster* PlayerInGame::getCardsPlaced() {
    return _cardsPlaced;
}


/**
 * Returns the cards in hand
 * @return the vector of card in hand
 */
std::vector<Card*> PlayerInGame::getCardsInHand() {
    return _cardsInHand;
}


/**
 * Return the size of card in hand
 */
unsigned PlayerInGame::nbrCardInHand() {
    return getCardsInHand().size();
}


/**
 * Get defausse card
 * @return the vector of defausse card
 */
std::vector<Card*> PlayerInGame::getDefausse() {
    return _defausse;
}


/**
 * Get defausse size
 */
unsigned PlayerInGame::nbrCardDefausse() {
    return getDefausse().size();
}



//////////// Deck info ////////////

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
 * Get the current deck
 *
 * @return the deck
 */
Deck* PlayerInGame::getDeck() {
    return _deck;
}


/**
 * Get number of card in the deck
 */
unsigned PlayerInGame::nbrCardDeck() {
    return getDeck()->size();
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



//////////// Game info ////////////

/**
 * Check if the player have enought energy to play a certain card
 * @param card the card to test
 * @return true if all is ok
 */
bool PlayerInGame::haveEnoughEnergy(Card* card) {
    return this->_energy > 0 &&
        card->getEnergyCost() <= static_cast<unsigned>(this->_energy);
}


/**
 * Increment the max energy of the player (if possible)
 */
void PlayerInGame::addMaxEnergy() {
    if (_maxEnergy < MAX_ENERGY) {
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


/**
 * Remove card from the placed card to the defausse
 *
 * @param cardPosition position of the card that must be defausse
 * @return noError if all is ok or error
 */
Error PlayerInGame::defausseCardPlaced(unsigned cardPosition) {
    Error res = Error::CardNotFound;

    if(_cardsPlaced[cardPosition] != nullptr) {
        _defausse.push_back(_cardsPlaced[cardPosition]);
        _cardsPlaced[cardPosition] = nullptr;
        res = Error::NoError;
    }

    return res;
}


/**
 * Defausse a card
 *
 * @param card wich must remove
 * @return noError if all is ok or error
 */
Error PlayerInGame::defausseCardInHand(Card* card) {
    Error res = Error::CardNotFound;
    std::vector<Card*>::iterator it = std::find(_cardsInHand.begin(), _cardsInHand.end(), card);
    if(it != _cardsInHand.end()) {
        _cardsInHand.erase(it);
        _defausse.push_back(card);
        res = Error::NoError;
    }

    return res;
}

/**
 * Place the card to the board
 *
 * @param card which must be placed
 * @return -1 if not enought place
 */
int PlayerInGame::placeCard(CardMonster* card) {
    unsigned res = -1;
    bool find = false;

    while(res < MAX_POSED_CARD && !find) {
        ++res;
        find = (_cardsPlaced[res] == nullptr);
    }

    if(find) {
        _cardsPlaced[res] = card;
    } else {
        res = -1;
    }

    return res;
}


/**
 * Remove heal of this player
 *
 * @param damage quantity of heal to remove
 */
void PlayerInGame::takeDamage(unsigned int damage){
    _playerHeal -= damage;
}


/**
 * Add heal of this player
 *
 * @param heal quantity of heal to add
 */
void PlayerInGame::addHeal(unsigned int heal){
    const int maxHP = MAX_LIFE;
    _playerHeal += heal;
    if(_playerHeal > maxHP) {
        _playerHeal = maxHP; //Can't go higher than the max
    }
}


/**
 * Get the number of heal
 *
 * @return the heal of this player
 */
int PlayerInGame::getHeal() {
    return _playerHeal;
}


/**
 * Checks if the player is Dead
 */
bool PlayerInGame::isDead() {
    return _playerHeal <= 0;
}

/**
 * Increment the number of turn for all placed cards
 */
void PlayerInGame::incrementAllPlaceCard() {
    CardMonster* cardPlaced = getCardsPlaced();
    for (size_t i = 0; i < MAX_POSED_CARD; ++i) {
        CardMonster* cardMonster = cardPlaced[i];
        if(cardMonster != nullptr) {
            cardMonster->incrementTour();
        }
    }
}

/**
 * Verify if the player have a Taunt card
 *
 * @return True if he have one taunt card
 */
bool PlayerInGame::haveOneCardTaunt() {
    bool res = true;

    CardMonster* cardPlaced = getCardsPlaced();
    unsigned i = 0;
    while(i < MAX_POSED_CARD && res) {
        CardMonster* currentCard = cardPlaced[i];
        if(currentCard != nullptr) {
            res = !(currentCard->isTaunt());
        }
        ++i;
    }

    return res;
}


/**
 * Check if the player have enought place on the board
 * to place a card
 *
 * @return true if enought place
 */
bool PlayerInGame::havePlace() {
    unsigned i = 0;
    bool res = false;
    while(i < MAX_POSED_CARD && !res) {
        res = (getCardsPlaced()[i] == nullptr);
    }

    return res;
}


/**
 * Get the game
 *
 * @return the game of this player
 */
Game* PlayerInGame::getGame() {
    return _game;
}


//////////// Game End /////////////

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


///////////////////////////////////

/**
 * Destructor
 */
PlayerInGame::~PlayerInGame() {
    _playerConnect->removePlayerInGame(this);
}
