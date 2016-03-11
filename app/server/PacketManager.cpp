#include "PacketManager.hpp"

#include "Player.hpp"
#include "PlayerInGame.hpp"
#include "Game.hpp"

void PacketManager::managePacket(Player *player, Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {
        /* Login process */
        case Packet::LOGIN_REQ_ID :       WizardLogger::warning("ATTENTION, les requêtes de login doivent directement être gérée");
                                          break;
        case Packet::REGIST_REQ_ID :      WizardLogger::warning("ATTENTION, les requêtes d'inscription doivent directement être gérée");
                                          break;
        case Packet::LOGIN_RES_ID :       WizardLogger::warning("Paquet de résolution de login reçu");
                                          break;
        case Packet::PLAYER_INFO_ID :     WizardLogger::warning("Paquet de résolution de login reçu");
                                          break;
        case Packet::DISCONNECT_ID :      manageDisconnectRequest(player, customPacket);
                                          break;
        /* Card process */
        case Packet::CARTE_REQ_ID :       manageCardRequest(player, (Packet::intPacket*) customPacket);
                                          break;
        case Packet::CARTE_INFO_ID :      WizardLogger::warning("Paquet d'info de carte reçu");
                                          break;
        case Packet::CARTE_IMG_REQ_ID :   manageCardImgRequest(player, (Packet::intPacket*) customPacket);
                                          break;
        case Packet::CARTE_IMG_ID :       WizardLogger::warning("Paquet d'image reçu");
                                          break;
        /* Tchat process */
        case Packet::TCHAT_CONV_REQ_ID :  manageConvRequest(player, (Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::TCHAT_NEW_CONV_ID :  WizardLogger::warning("Paquet de nouvelle conversation (tchat) reçu");
                                          break;
        case Packet::TCHAT_MESSAGE_ID :   manageMessageTchat(player, (Packet::tchatMessagePacket*) customPacket);
                                          break;
        case Packet::TCHAT_END_REQ_ID :   manageConvQuitRequest(player, (Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::TCHAT_END_CONV_ID :  WizardLogger::warning("Paquet de fin de conversation (tchat) reçu");
                                          break;
        /* Friend process */
        case Packet::FRIEND_ADD_ID :      manageFriendRequest(player, (Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::FRIEND_DEL_ID :      manageFriendRequest(player, (Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::FRIENDS_REQ_ID :     WizardLogger::warning("Paquet de requête d'ami reçu");
                                          break;
        case Packet::FRIENDS_LIST_REQ_ID :manageFriendListRequest(player, customPacket);
                                          break;
        case Packet::FRIENDS_LIST_ID :    WizardLogger::warning("Paquet de liste d'ami reçu");
                                          break;
        /* Launching game process */
        case Packet::WAITING_ID :         managNewGameRequest(player, customPacket);
                                          break;
        case Packet::CANCEL_ID :          managCancelGameRequest(player, customPacket);
                                          break;
        case Packet::LAUNCH_ID :          WizardLogger::warning("Paquet de lancement de partie reçu");
                                          break;
        case Packet::DECK_CHOOS_ID :      manageChooseDeck(player, (Packet::intPacket*) customPacket);
                                          break;
        /* Game process */
        case Packet::TURN_ID :            WizardLogger::warning("Paquet d'informations de tours reçu");
                                          break;
        case Packet::DRAW_ID :            WizardLogger::warning("Paquet de carte pioché reçu");
                                          break;
        case Packet::ASK_DROP_ID :        WizardLogger::warning("Paquet de demande de drop de carte reçu");
                                          break;
        case Packet::DROP_ID :            manageDrop(player, (Packet::intPacket*) customPacket);
                                          break;
        case Packet::ATTACK_ID :          manageAttack(player, (Packet::attackPacket*) customPacket);
                                          break;
        case Packet::SPELL_ID :           manageSpell(player, (Packet::attackPacket*) customPacket);
                                          break;
        case Packet::END_TURN_ID :        manageEndTurn(player, customPacket);
                                          break;
        case Packet::QUIT_ID :            manageQuitGame(player, customPacket);
                                          break;
        case Packet::END_GAME_ID :        WizardLogger::warning("Paquet de fin de partie reçu");
                                          break;
        default :                         WizardLogger::warning("Paquet inconnue reçu");
                                          break;
    }
}

//===========================LOGIN PROCESS===========================================

void PacketManager::manageDisconnectRequest(Player* player, Packet::packet* disconnectPacket) {
    WizardLogger::info(player->getName()+" se déconnecte");
    player->logout();
}

//============================CARD PROCESS===========================================

void PacketManager::manageCardRequest(Player* player, Packet::intPacket* cardRequest) {
    //TODO get card form server database and call sendCardInfo (block client recev :/)
}

void PacketManager::manageCardImgRequest(Player* player, Packet::intPacket* cardRequest) {
    //TODO get card form server database and call sendCardImg (block client recev :/)
}

/* Send all card's info to the client
 * @param player : the player who to send this packet
 * @param card : the card's info needed
 */
void PacketManager::sendCardInfo(Player* player, Card* card) {
    //TODO send card info (no img) to the client
}


/* Send card img to the client
 * @param player : the player who to send this packet
 * @param card : the card's img needed
 */
void PacketManager::sendCardImg(Player* player, Card* card) {
    //TODO send card img to the client
}

//============================TCHAT PROCESS===========================================

void PacketManager::manageConvRequest(Player* player, Packet::pseudoPacket* convReqPacket) {
    //TODO must call tchatManager (must be unblocking)
}

void PacketManager::manageMessageTchat(Player* player, Packet::tchatMessagePacket* messagePacket) {
    //TODO must call tchatManager (must be unblocking)
}

void PacketManager::manageConvQuitRequest(Player* player, Packet::pseudoPacket* convReqPacket) {
    //TODO must call tchatManager (must be unblocking)
}

/* Signal a new conversation to the client
 * @param player : the player who to send this packet
 * @param pseudo : the other player's pseudo
 */
void PacketManager::startConv(Player* player, std::string pseudo) {
    Packet::pseudoPacket *newConvPacket = new Packet::pseudoPacket;
    
    /* Set ID and pseudo */
    newConvPacket->ID = Packet::TCHAT_NEW_CONV_ID;
    for (int i = 0 ; i < pseudo.size() ; ++i) newConvPacket->pseudo[i] = pseudo[i];
    
    /* Send and free */
    player->sendPacket((Packet::packet*) newConvPacket, sizeof(*newConvPacket));
    delete newConvPacket;
}

/* Send a message to the client
 * @param player : the player who to send this packet
 * @param message : the string to send (!> MESSAGES_MAX_SIZE)
 */
void PacketManager::sendMessageTchat(Player* player, std::string message) {
    Packet::tchatMessagePacket *messagePacket = new Packet::tchatMessagePacket;
    
    /* Set message */
    for (int i = 0 ; i < message.size() ; ++i) messagePacket->msg[i] = message[i];
    
    /* Send and free */
    player->sendPacket((Packet::packet*) messagePacket, sizeof(*messagePacket));
    delete messagePacket;
}

/* Signal the end of the conversation between pseudo's player and the client
 * @param player : the player who to send this packet
 * @param pseudo : other player
 */
void PacketManager::endConv(Player* player, std::string pseudo) {
    Packet::pseudoPacket *endConvPacket = new Packet::pseudoPacket;
    
    /* Set ID and pseudo */
    endConvPacket->ID = Packet::TCHAT_END_CONV_ID;
    for (int i = 0 ; i < pseudo.size() ; ++i) endConvPacket->pseudo[i] = pseudo[i];
    
    /* Send and free */
    player->sendPacket((Packet::packet*) endConvPacket, sizeof(*endConvPacket));
    delete endConvPacket;
}

//============================FRIEND PROCESS===========================================

void PacketManager::manageFriendRequest(Player* player, Packet::pseudoPacket* friendRequest) {
    //TODO call friendManager (must be unblocking) [if friend exist - delete it]
}

void PacketManager::manageFriendListRequest(Player* player, Packet::packet* packet) {
    //TODO get friendList form player and call sendFriendList (block client recev :/)
}


/* Signal to the client a new friend request
 * If deny, must signal FRIEND_DEL_ID to other player
 * @param player : the player who to send this packet
 * @param pseudo : the other player's pseudo
 */
void PacketManager::sendFriendRequest(Player* player, std::string pseudo) {
    Packet::pseudoPacket *friendRequest = new Packet::pseudoPacket;
    
    /* Set ID and pseudo */
    friendRequest->ID = Packet::FRIENDS_LIST_ID;
    for (int i = 0 ; i < pseudo.size() ; ++i) friendRequest->pseudo[i] = pseudo[i];
    
    /* Send and free */
    player->sendPacket((Packet::packet*) friendRequest, sizeof(*friendRequest));
    delete friendRequest;
}

/* Send all friend to the player
 * @param player : the player who to send this packet
 */
void PacketManager::sendFriendList(Player* player) {
    //TODO
}

//============================LAUNCHING PROCESS=========================================

void PacketManager::managNewGameRequest(Player* player, Packet::packet* packet) {
    Game::addPlayerWaitGame(player);
}

void PacketManager::managCancelGameRequest(Player* player, Packet::packet* packet) {
    //TODO call cancel waiting in Game
}
void PacketManager::manageChooseDeck(Player* player, Packet::intPacket* deckChoosPacket) {
    //TODO manage choosen deck ID and inform party
}

//==============================GAME PROCESS============================================

/* Init game and give player pseudo of his ennemy
 * @param player : the player who to send this packet
 * @param ennemyPseudo
 */
void PacketManager::initGame(Player *player, std::string ennemyPseudo) {
    Packet::pseudoPacket *newGamePacket = new Packet::pseudoPacket;
    
    /* Set ID and ennemy's pseudo */
    newGamePacket->ID = Packet::LAUNCH_ID;
    for (int i = 0 ; i < ennemyPseudo.size() ; ++i) newGamePacket->pseudo[i] = ennemyPseudo[i];
    
    /* Send and free */
    player->sendPacket((Packet::packet*) newGamePacket, sizeof(*newGamePacket));
    delete newGamePacket;
}

void PacketManager::manageDrop(Player* player, Packet::intPacket* dropIDPacket) {
    //TODO tell Game wich card is drop
}

void PacketManager::manageAttack(Player* player, Packet::attackPacket* attackPacket) {
    //TODO tell Game about attack
}

void PacketManager::manageSpell(Player* player, Packet::attackPacket* spellPacket) {
    //TODO tell Game about spell
}

void PacketManager::manageEndTurn(Player* player, Packet::packet* packet) {
    //TODO tell Game about end of turn
}

void PacketManager::manageQuitGame(Player* player, Packet::packet* packet) {
    //TODO tell Game about (rage) quit
}

/* Send all info needed for sync to the client
 * @param player : the player who to send this packet
 * @param currentPlayer : the player who his the turn
 * @param playerInGame : the player (in-game)
 * @param ennemyInGame : the ennemy player (in-game)
 */
void PacketManager::sendTurnInfo(Player* player, std::string currentPlayer, PlayerInGame* playerInGame, PlayerInGame* ennemyInGame) {
    //TODO Send all info for sync
}

/* Send draw card to the player
 * @param player : the player who to send this packet
 * @param card : new drawed card
 */
void PacketManager::sendCard(Player* player, Card* card) {
    Packet::intPacket *drawPacket = new Packet::intPacket;
    
    /* Set ID and ID */
    drawPacket->ID = Packet::DRAW_ID;
    drawPacket->data = card->getId();
    
    /* Send and free */
    player->sendPacket((Packet::packet*) drawPacket, sizeof(*drawPacket));
    delete drawPacket;
}

/* Ask player to drop a certain amount of card
 * @param player : the player who to send this packet
 * @param amount : nbr of card to drop
 */
void PacketManager::askDefausse(Player* player, int amount) {
    Packet::intPacket *askDropPacket = new Packet::intPacket;
    
    /* Set ID and amount */
    askDropPacket->ID = Packet::ASK_DROP_ID;
    askDropPacket->data = amount;
    
    /* Send and free */
    player->sendPacket((Packet::packet*) askDropPacket, sizeof(*askDropPacket));
    delete askDropPacket;
}

/* Send droped card to the player
 * @param player : the player who to send this packet
 * @param card : new droped card (-1 for sync)
 */
void PacketManager::sendDrop(Player* player, int ID) {
    Packet::intPacket *dropPacket = new Packet::intPacket;
    
    /* Set ID and amount */
    dropPacket->ID = Packet::DROP_ID;
    dropPacket->data = ID;
    
    /* Send and free */
    player->sendPacket((Packet::packet*) dropPacket, sizeof(*dropPacket));
    delete dropPacket;
}

/**
 * Send attack informations
 * @param player : the player who to send this packet
 * @param pseudo : attacking player's pseudo
 * @param targetID : ID of the target (-1 for player, other for cardMonster)
 * @param cardWichAttack : Card which attack the other
 * @param finalLife : final life of the target after attack
 */
void PacketManager::sendAttack(Player* player, std::string pseudo, int targetID, int cardWichAttack, unsigned int finalLife) {
    Packet::attackPacket *attackPacket = new Packet::attackPacket;
    
    /* Set ID and other info */
    attackPacket->ID = Packet::ATTACK_ID;
    for (int i = 0 ; i < pseudo.size() ; ++i) attackPacket->data.pseudo[i] = pseudo[i];
    attackPacket->data.target = targetID;
    attackPacket->data.ID = cardWichAttack;
    attackPacket->data.finalLife = finalLife;
    
    /* Send and free */
    player->sendPacket((Packet::packet*) attackPacket, sizeof(*attackPacket));
    delete attackPacket;
}

/**
 * Send spell informations
 * @param player : the player who to send this packet
 * @param pseudo : attacking player's pseudo
 * @param ID : Card which do spell
 * @param targetID : ID of the target (-1 for player, other for cardMonster)
 * @param finalLife : final life of the target after attack
 */
void PacketManager::sendSpell(Player* player, std::string pseudo, int ID, int targetID, unsigned int finalLife) {
    Packet::attackPacket *spellPacket = new Packet::attackPacket;
    
    /* Set ID and other info */
    spellPacket->ID = Packet::SPELL_ID;
    for (int i = 0 ; i < pseudo.size() ; ++i) spellPacket->data.pseudo[i] = pseudo[i];
    spellPacket->data.ID = ID;
    spellPacket->data.target = targetID;
    spellPacket->data.finalLife = finalLife;
    
    /* Send and free */
    player->sendPacket((Packet::packet*) spellPacket, sizeof(*spellPacket));
    delete spellPacket;
}

/* Send end game signal (victory or defeat)
 * @param player : the player who to send this packet
 * @param victory : 1 say win, -1 lose and 0 if player disconnect
 * @param card : card's ID win
 */
void PacketManager::sendEndGame(Player* player, int victory, int card) {
    Packet::endGamePacket *endPacket = new Packet::endGamePacket;
    
    /* Set victory flag and card ID (-1 for no card) */
    endPacket->data.victory = victory;
    endPacket->data.card = card;
    
    /* Send and free */
    player->sendPacket((Packet::packet*) endPacket, sizeof(*endPacket));
    delete endPacket;
}
