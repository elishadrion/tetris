
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
PlayerInGame::PlayerInGame(Player player) {
    // TO DO
}

/**
 * Send all information about the player and the game
 *
 * @param currentPlayer who must play
 * @param turn of the game
 * @param adversePlacedCards list of card placed by adverse player
 */
void PlayerInGame::sendData(unsigned int currentPlayer, unsigned int turn,
    std::vector<Card*> adversePlacedCards) {
    // to do
}

/**
 * Return the placed card
 */
std::vector<Card*> PlayerInGame::getCardPlaced() {
    return _cardsPlaced;
}

