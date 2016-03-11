#include "PacketManager.hpp"

#include "Player.hpp"
#include "Game.hpp"

void PacketManager::managePacket(Player *player, Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {
        case Packet::LOGIN_REQ_ID :       WizardLogger::warning("ATTENTION, les requêtes de login doivent directement être gérée");
                                          break;
        case Packet::REGIST_REQ_ID :      WizardLogger::warning("ATTENTION, les requêtes d'inscription doivent directement être gérée");
                                          break;
        case Packet::DISCONNECT_ID :      PacketManager::manageDisconnectRequest(player, customPacket);
                                          break;
        case Packet::WAITING_ID :         PacketManager::managNewGameRequest(player, customPacket);
                                          break;
        case Packet::CANCEL_ID :          PacketManager::manageCancelWait(player, customPacket);
                                          break;
        default :                         WizardLogger::warning("Paquet inconnue reçu");
                                          break;
    }
}

//==========================================================================================================

/* Init game and give player pseudo of his ennemy
 * @param player : the players who to send this packet
 * @param ennemyPseudo
 */
void PacketManager::initGame(Player *player, std::string ennemyPseudo) {
    Packet::managPacket *newGamePacket = new Packet::managPacket;
    newGamePacket->ID = Packet::LAUNCH_ID;
    for (int i = 0 ; i < ennemyPseudo.size() ; ++i) newGamePacket->pseudo[i] = ennemyPseudo[i];
    player->sendPacket((Packet::packet*) newGamePacket, sizeof(*newGamePacket));
    delete newGamePacket;
}

/* Send a draw card to the player
 * @param player : the players who to send this packet
 * @param card : the drawed card
 */
void PacketManager::sendCard(Player *player, Card *card) {
}

/* Notify wich turn is it
 * @param player : the players who to send this packet
 * @param pseudo : the player's pseudo of current turn
 */
void PacketManager::setTurn(Player *player, std::string pseudo) {
}

/**
 * Send informations when the player start he turn
 *
 * @param player : the players who to send this packet
 * @param energy : energy that have the player
 * (it is egal at he max energy)
 * @param adverseCardInHand : number of card that the
 * adverse player have
 */
void PacketManager::sendInfoStartTurn(Player *player, int energy,
    int adverseCardInHand) {

}


/**
 * Send attack informations
 *
 * @param player : the players who to send this packet
 * @param pseudo : attacking player's pseudo
 * @param targetID : ID of the target (-1 for player, other for cardMonster)
 * @param cardWichAttack : Card which attack the other
 * @param isEffect : if the attack is an effect (false if it is attack)
 * @param newCard : true if it's a new card wich make attack
 * @param finalLife : final life of the target after attack
 */
void PacketManager::sendAttack(Player *player, std::string pseudo, int cardWichAttack,
    int targetID, bool isEffect, bool newCard, unsigned int finalLife) {
}

/* Ask player to defausse a specific amount of card before continue
 * @param player : the players who to send this packet
 * @param amount : nbr of card player must defausse
 */
void PacketManager::askDefausse(Player *player, int amount) {
}

/* Send end game signal (victory or defeat)
 * @param player : the players who to send this packet
 * @param victory : 1 say win, -1 lose and 0 if advers player disconnect
 */
void PacketManager::sendEndGame(Player *player, int victory) {
}

//==========================================================================================================

void PacketManager::manageDisconnectRequest(Player *player, Packet::packet* disconnectReqPacket) {
    WizardLogger::info(player->getName()+" se déconnecte");
    player->logout();
}

void PacketManager::manageCancelWait(Player *player, Packet::packet* cancelReqPacket) {
    Game::removePlayerWaitGame(player);
}

void PacketManager::managNewGameRequest(Player *player, Packet::packet* newGameRequest) {
    Game::addPlayerWaitGame(player);
}
