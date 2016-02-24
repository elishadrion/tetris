#include "PacketManager.hpp"

void PacketManager::managePacket(Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {
        case Packet::LOGIN_REQ_ID :       WizardLogger::warning("ATTENTION, les requêtes de login doivent directement être appelé");
                                          break;
        case Packet::REGIST_REQ_ID :      WizardLogger::warning("ATTENTION, les requêtes d'inscription doivent directement être appelé");
                                          break;
        case Packet::DISCONNECT_ID :      PacketManager::manageDisconnectRequest(customPacket);
                                          break;
        case Packet::COLLECTION_REQ_ID :  //TODO
                                          break;
        case Packet::COLLECTION_LIST_ID : WizardLogger::warning("Paquet invalide reçu : CollectionList");
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
void initGame(Player *player, std::string ennemyPseudo) {
}

/* Send all needed informations to the client
 * @param player : the players who to send this packet
 * @param playerInfo : current player's informations
 * @param ennemyCard : ennemy's placed card
 * @param ennemyHandCount : nbr of card in ennemy's hand
 * @param ennemyDeckCount : nbr of card in ennemy's deck
 * @param ennemyTrashCount : nbr of card in ennemy's trash
 */
void sendStartTurnInfo(Player *player, dataIGPlayer playerInfo, std::vector<CardMonster*> ennemyCard,
int ennemyHandCount, int ennemyDeckCount, int ennemyTrashCount) {
}

/* Send a draw card to the player
 * @param player : the players who to send this packet
 * @param card : the drawed card
 */
void sendCrard(Player *player, Card *card) {
}

/* Notify wich turn is it
 * @param player : the players who to send this packet
 * @param pseudo : the player's pseudo of current turn
 */
void setTurn(Player *player, std::string pseudo) {
}

/* Send attack informations
 * @param player : the players who to send this packet
 * @param pseudo : attacking player's pseudo
 * @param targetID : ID of the target (-1 for player, other for cardMonster)
 * @param finalLife : final life of the target after attack
 */
void sendAttack(Player *player, std::string pseudo, int targetID, unsigned int finalLife) {
}

/* Ask player to defausse a specific amount of card before continue
 * @param player : the players who to send this packet
 * @param amount : nbr of card player must defausse
 */
void askDefausse(Player *player, int amount) {
}

/* Send end game signal (victory or defeat)
 * @param player : the players who to send this packet
 * @param victory : is current player win or no ? (didn't support equality, is it important ?)
 */
void sendEndGame(Player *player, bool victory) {
}

//==========================================================================================================

void PacketManager::manageDisconnectRequest(Packet::packet* disconnectReqPacket) {
    
}
