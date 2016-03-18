#include "PacketManager.hpp"

#include "Player.hpp"
#include "PlayerInGame.hpp"
#include "Game.hpp"

void PacketManager::managePacket(Player *player, Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {
        /* Login process */
        case Packet::LOGIN_REQ_ID :       WizardLogger::warning(
                                            "ATTENTION, les requêtes de login doivent directement être gérée");
                                          break;
        case Packet::REGIST_REQ_ID :      WizardLogger::warning(
                                            "ATTENTION, les requêtes d'inscription doivent directement être gérée");
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
        case Packet::ASK_DECK_ID :        WizardLogger::warning("Paquet d'initialisation de la partie reçu");
                                          break;
        case Packet::GAME_START_ID:       WizardLogger::warning("Paquet de début de partie reçu");
                                          break;
        case Packet::DECK_CHOOS_ID :      manageChooseDeck(dynamic_cast<PlayerInGame*>(player),
                                                           (Packet::deckPacket*) customPacket);
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
        case Packet::C_ATTACK_ID:         manageAttack(player, (Packet::twoCardPacket*) customPacket);
                                          break;
        case Packet::C_PLACE_CARD_ID:
                                          break;
        case Packet::C_PLACE_SPELL_ID:
                                          break;
        case Packet::C_PLACE_CARD_MAKE_SPELL_ID:

                                          break;
        case Packet::S_ATTACK_ID:         WizardLogger::warning("Packet d'attack d'une carte (serveur)");
                                          break;
        case Packet::S_PLACE_CARD_ID:     WizardLogger::warning("Packet pour poser une carte (serveur)");
                                          break;
        case Packet::S_PLACE_SPELL_ID:    WizardLogger::warning("Packet pour poser une carte sort (serveur)");
                                          break;
        case Packet::END_TURN_ID :        manageEndTurn(player, customPacket);
                                          break;
        case Packet::QUIT_ID :            manageQuitGame(player, customPacket);
                                          break;
        case Packet::END_GAME_ID :        WizardLogger::warning("Paquet de fin de partie reçu");
                                          break;
        /* Classement process */
        case Packet::ASK_CLASSEMENT_ID:   PlayerManager::sendRanking(player);
                                          break;
        case Packet::SEND_CLASSEMENT_ID:  WizardLogger::warning("Packet pour envoyer le classement reçu");
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
    Packet::pseudoPacket *newConvPacket = new Packet::pseudoPacket();
    
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
    Packet::tchatMessagePacket *messagePacket = new Packet::tchatMessagePacket();
    
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
    Packet::pseudoPacket *endConvPacket = new Packet::pseudoPacket();
    
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
    Packet::pseudoPacket *friendRequest = new Packet::pseudoPacket();
    
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
void PacketManager::manageChooseDeck(Player* player, Packet::deckPacket* deckChoosPacket) {
    WizardLogger::info("Deck sélectionné pour " + player->getName());
    if(player->isPlayerInGame()) {
        static_cast<PlayerInGame*>(player)->setDeck(deckChoosPacket->deck);
        WizardLogger::info("PLAYER in game pour le set deck");
    }
    //TODO
}

//==============================GAME PROCESS============================================

/**
 * Ask to the player witch deck he would like
 *
 * @param player the player
 */
void PacketManager::askDeck(Player *player) {
    WizardLogger::info("Demande à : " + player->getName() +
                       " de choisir son deck");

    Packet::packet *newGamePacket = new Packet::packet();

    /* Set ID and ennemy's pseudo */
    newGamePacket->ID = Packet::ASK_DECK_ID;

    /* Send and free */
    player->sendPacket((Packet::packet*) newGamePacket, sizeof(*newGamePacket));
    delete newGamePacket;
}

/**
 * Init game and give player pseudo of his ennemy
 *
 * @param player : the player who to send this packet
 * @param ennemyPseudo
 */
void PacketManager::initGame(Player *player, std::string ennemyPseudo) {
    WizardLogger::info("Information de début de partie: " + player->getName() +
                       " > " + ennemyPseudo);

    Packet::pseudoPacket *newGamePacket = new Packet::pseudoPacket();
    
    /* Set ID and ennemy's pseudo */
    newGamePacket->ID = Packet::GAME_START_ID;
    for (int i = 0 ; i < ennemyPseudo.size() ; ++i) newGamePacket->pseudo[i] = ennemyPseudo[i];
    
    /* Send and free */
    player->sendPacket((Packet::packet*) newGamePacket, sizeof(*newGamePacket));
    delete newGamePacket;
}

void PacketManager::manageDrop(Player* player, Packet::intPacket* dropIDPacket) {
    //TODO tell Game wich card is drop
}

void PacketManager::manageAttack(Player *player, Packet::twoCardPacket* attackPacekt) {
    if(player->isPlayerInGame()) {
        // TO DO
    } else {
        WizardLogger::warning("ManageAttack appellé par un player et non un PlayerInGame");
    }
}

void PacketManager::manageEndTurn(Player* player, Packet::packet* packet) {
    //TODO tell Game about end of turn
}

void PacketManager::manageQuitGame(Player* player, Packet::packet* packet) {
    //TODO tell Game about (rage) quit
}

/**
 * Send all info needed for sync to the clients
 * @param currentPlayer : the player who his the turn
 * @param playerInGame : the player (in-game)
 * @param ennemyInGame : the ennemy player (in-game)
 */
void PacketManager::sendTurnInfo(PlayerInGame* current, PlayerInGame* adverse, bool hisTurn) {
    //TODO modification because inutilised information

    Packet::turnPacket *turnPacket =  new Packet::turnPacket();

    turnPacket->data.turn = hisTurn;

    turnPacket->data.life = current->getHeal();

    std::vector<Card*> listDefausse = current->getDefausse();
    for(unsigned i = 0; i < listDefausse.size(); ++i) {
        turnPacket->data.trash[i] = static_cast<Card*>(listDefausse[i])->getId();
    }

    std::vector<Card*> listHand = current->getCardsInHand();
    for(unsigned i = 0; i < listHand.size(); ++i) {
        turnPacket->data.hand[i] = static_cast<Card*>(listHand[i])->getId();
    }

    std::vector<unsigned> listDeckId = static_cast<Deck*>(current->getDeck())->getCardsId();
    for(unsigned i = 0; i < listDeckId.size(); ++i) {
        turnPacket->data.deck[i] = listDeckId[i];
    }

    std::vector<CardMonster*> listCardPlace = current->getCardsPlaced();
    for(unsigned i = 0; i < listCardPlace.size(); ++i) {
        CardMonster* currentCardMonster = static_cast<CardMonster*>(listCardPlace[i]);
        turnPacket->data.posed[i] = currentCardMonster->getId();
        turnPacket->data.posedLife[i] = currentCardMonster->getLife();
    }

    turnPacket->data.ennemyLife = adverse->getHeal();
    turnPacket->data.ennemyTrash = adverse->nbrCardDefausse();
    turnPacket->data.ennemyHand = adverse->nbrCardInHand();
    turnPacket->data.ennemyDeck = adverse->nbrCardDeck();

    std::vector<CardMonster*> listAdverseCardPlace = adverse->getCardsPlaced();
    for(unsigned i = 0; i < listAdverseCardPlace.size(); ++i) {
        CardMonster* currentCardMonster = static_cast<CardMonster*>(listAdverseCardPlace[i]);
        turnPacket->data.ennemyPosed[i] = currentCardMonster->getId();
        turnPacket->data.ennemyPosedLife[i] = currentCardMonster->getLife();
    }


    /* Send and free */
    current->sendPacket((Packet::packet*) turnPacket, sizeof(*turnPacket));
    delete turnPacket;

}

/**
 * Send draw card to the player
 * @param player : the player who to send this packet
 * @param card : new drawed card
 */
void PacketManager::sendCard(Player* player, Card* card) {
    Packet::intPacket *drawPacket = new Packet::intPacket();
    
    /* Set ID and ID */
    drawPacket->ID = Packet::DRAW_ID;
    drawPacket->data = card->getId();
    
    /* Send and free */
    player->sendPacket((Packet::packet*) drawPacket, sizeof(*drawPacket));
    delete drawPacket;
}

/**
 * Ask player to drop a certain amount of card
 * @param player : the player who to send this packet
 * @param amount : nbr of card to drop
 */
void PacketManager::askDefausse(Player* player, int amount) {
    Packet::intPacket *askDropPacket = new Packet::intPacket();
    
    /* Set ID and amount */
    askDropPacket->ID = Packet::ASK_DROP_ID;
    askDropPacket->data = amount;
    
    /* Send and free */
    player->sendPacket((Packet::packet*) askDropPacket, sizeof(*askDropPacket));
    delete askDropPacket;
}

/**
 * Send droped card to the player
 * @param player : the player who to send this packet
 * @param card : new droped card (-1 for sync)
 */
void PacketManager::sendDrop(Player* player, int ID) {
    Packet::intPacket *dropPacket = new Packet::intPacket();
    
    /* Set ID and amount */
    dropPacket->ID = Packet::DROP_ID;
    dropPacket->data = ID;
    
    /* Send and free */
    player->sendPacket((Packet::packet*) dropPacket, sizeof(*dropPacket));
    delete dropPacket;
}


/**
 * Call when card attack an other
 *
 * @param player player who must recieve information
 * @param pseudo of the player who place
 * @param cardPosition position of the card the is placed
 * @param targetPosition position of the card wich have dammage
 * @param heal of the target card
 */
void PacketManager::sendAttack(Player* player, std::string pseudo, int cardPosition, int targetPosition,
                               unsigned heal) {

    Packet::attackPacket* attackPacket = new Packet::attackPacket();

    for (int i = 0 ; i < pseudo.size() ; ++i) attackPacket->data.pseudo[i] = pseudo[i];
    attackPacket->data.cardPosition = cardPosition;
    attackPacket->data.targetPosition = targetPosition;
    attackPacket->data.heal = heal;

    /* Send and free */
    player->sendPacket((Packet::packet*) attackPacket, sizeof(*attackPacket));
    delete attackPacket;
}


/**
 * Call when a card monster is placed
 *
 * @param player who must recieve information
 * @param pseudo of the player who place
 * @param cardID wich is placed
 * @param cardPosition position of the card in the board
 */
void PacketManager::sendPlaceMonsterCard(Player* player, std::string pseudo, int cardID, int cardPosition) {
    Packet::placeCardPacket* placeCardPacket = new Packet::placeCardPacket();

    for (int i = 0 ; i < pseudo.size() ; ++i) placeCardPacket->pseudo[i] = pseudo[i];
    placeCardPacket->idCard = cardID;
    placeCardPacket->cardPosition = cardPosition;

    // Send and free
    player->sendPacket((Packet::packet*) placeCardPacket, sizeof(*placeCardPacket));
    delete placeCardPacket;
}

/**
 * Call when card monster is placed and he attack somethink
 *
 * @param player player who must recieve information
 * @param pseudo of the player who place
 * @param cardID wich is placed
 * @param cardPosition position of the new card
 * @param targetPosition position of the attack card
 * @param heal of the target card
 */
void PacketManager::sendPlaceMonsterCard(Player* player, std::string pseudo, int cardID, int cardPosition,
                                         int targetPosition, unsigned heal) {
    sendPrivatePlaceAttackPacket(player, pseudo, cardID, cardPosition, targetPosition, heal,
                                 Packet::S_PLACE_CARD_AND_ATTACK_ID);
}

/**
 * Call when card spell is placed
 *
 * @param player player who must recieve information
 * @param pseudo of the player who place
 * @param cardID wich is placed
 * @param cardPosition position of the new card
 * @param targetPosition position of the attack card
 * @param heal of the target card
 */
void PacketManager::sendPlaceSpellCard(Player* player, std::string pseudo, int cardID, int cardPosition,
                                       int targetPosition, unsigned heal) {
    sendPrivatePlaceAttackPacket(player, pseudo, cardID, cardPosition, targetPosition, heal,
                                 Packet::S_PLACE_SPELL_ID);
}


/**
 * PRIVATE function for place and attack packet
 *
 * @param player who must recieve information
 * @param pseudo of the player who place
 * @param cardID wich is placed
 * @param cardPosition position of the new card
 * @param targetPosition position of the attack card
 * @param heal of the target card
 * @param PacketID specific which packet
 */
void PacketManager::sendPrivatePlaceAttackPacket(Player* player, std::string pseudo, int cardID, int cardPosition,
                                                 int targetPosition, unsigned heal, int PacketID) {

    Packet::placeAttackPacket* placeAttackPacket = new Packet::placeAttackPacket();

    placeAttackPacket->ID = PacketID;
    for (int i = 0 ; i < pseudo.size() ; ++i) placeAttackPacket->data.pseudo[i] = pseudo[i];
    placeAttackPacket->data.idCard = cardID;
    placeAttackPacket->data.cardPosition = cardPosition;
    placeAttackPacket->data.targetPosition = targetPosition;
    placeAttackPacket->data.heal = heal;

    // Send and free
    player->sendPacket((Packet::packet*) placeAttackPacket, sizeof(*placeAttackPacket));
    delete placeAttackPacket;
}


/**
 * Send information about the new life of a player
 * @param player the play who to send this packet
 * @param pseudo who loose life
 * @param life new life of the player
 */
void PacketManager::playerDamage(Player* player, std::string pseudo, int life) {
    Packet::pseudoIntPacket* playerDamage = new Packet::pseudoIntPacket();

    playerDamage->ID = Packet::PLAYER_DAMAGE_ID;
    for (int i = 0 ; i < pseudo.size() ; ++i) playerDamage->pseudo[i] = pseudo[i];
    playerDamage->data = life;

    player->sendPacket((Packet::packet*) playerDamage, sizeof(*playerDamage));
    delete playerDamage;
}



/**
 * Send end game signal (victory or defeat)
 * @param player : the player who to send this packet
 * @param victory : 1 say win, -1 lose and 0 if player disconnect
 * @param card : card's ID win
 */
void PacketManager::sendEndGame(Player* player, int victory, int card) {
    Packet::endGamePacket *endPacket = new Packet::endGamePacket();
    
    /* Set victory flag and card ID (-1 for no card) */
    endPacket->data.victory = victory;
    endPacket->data.card = card;
    
    /* Send and free */
    player->sendPacket((Packet::packet*) endPacket, sizeof(*endPacket));
    delete endPacket;
}



//=================================== CLASSEMENT ======================================
/**
 * Send the 50 best player stats
 *
 * @param player who would like recieve informations
 * @param list_name list of playerName
 * @param list_victories list of victories
 * @param list_defeats list of defets
 */
void PacketManager::sendClassement(Player* player, std::vector<std::string> list_name,
                                   std::vector<int> list_victories, std::vector<int> list_defeats) {

    Packet::ClassementPacket *classementPacket = new Packet::ClassementPacket();

    // Asset: nombre de player == nombre de victoires == nombre de défaites

    // Set Player List
    for(unsigned i = 0; i < list_name.size(); ++i) {
        unsigned current = i*MAX_PSEUDO_SIZE;
        std::string pseudo = list_name[i];
        unsigned nbrChar;

        for(nbrChar = 0; nbrChar < pseudo.size(); ++nbrChar) {
            classementPacket->data.pseudo[current++] = pseudo[nbrChar];
        }

    }

    // Set victories & defeats
    for(unsigned i = 0; i < list_name.size(); ++i) {
        classementPacket->data.victories[i] = list_victories[i];
        classementPacket->data.defeats[i] = list_defeats[i];
    }


    /* Send and free */
    player->sendPacket((Packet::packet*) classementPacket, sizeof(*classementPacket));
    delete classementPacket;
}



