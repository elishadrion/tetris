
#include "PlayerInGame.hpp"



/**
 * Default constructor
 */
PlayerInGame::PlayerInGame() {
    // TO DO
}

/**
 * Create a PlayerInGame and ask to the player witch Deck he would like to play
 */
PlayerInGame::PlayerInGame(Player player, Game* game) {
    // TO DO
    // askDesck(getListDeck());
    // @tutul
}

/**
 * Get data information from this player to send it
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
 * Set the player deck and notify it at the game object
 *
 * @param deck The selected deck
 */
void PlayerInGame::setDeck(Deck *deck) {
    _deck = deck;
    game->checkDeckAndStart();
}
// @tutul méthode à appeller lorsque l'on recoit un deck


/**
 * Check if the deck of this player is define
 *
 * @return True if the deck is define
 */
bool PlayerInGame::isDeckDefine() {
    return _deck != nullptr;
}

/**
 * Get random cart of deck
 *
 * @return a random card
 */
//Card* PlayerInGame::draw() {
//    return CardManager::getCardById(_deck->pickup());
//}



/**
 * Return the placed card
 */
std::vector<Card*> PlayerInGame::getCardPlaced() {
    return _cardsPlaced;
}

