
#include "PlayerInGame.hpp"



/**
 * Default constructor
 */
PlayerInGame::PlayerInGame() {
    // TO DO
}

/**
 * Creates a PlayerInGame and asks to the player which Deck he would like to play with
 */
PlayerInGame::PlayerInGame(Player player, Game* game) {
    // TO DO
    // askDesck(getListDeck());
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

    return data;
}

/**
 * Sets the player deck and notify it at the game object
 *
 * @param deck The selected deck
 */
void PlayerInGame::setDeck(Deck *deck) {
    _deck = deck;
    game->checkDeckAndStart();
}
// @tutul méthode à appeler lorsque l'on recoit un deck


/**
 * Checks if the deck of this player is defined
 *
 * @return True if the deck is defined
 */
bool PlayerInGame::isDeckDefine() {
    return _deck != nullptr;
}

/**
 * Gets random card of deck
 *
 * @return a random card
 */
//Card* PlayerInGame::draw() {
//    return CardManager::getCardById(_deck->pickup());
//}



/**
 * Returns the placed cards
 */
std::vector<CardMonster*> PlayerInGame::getCardPlaced() {
    return _cardsPlaced;
}

