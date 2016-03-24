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
        case Packet::LOGIN_COMPLETE_ID :  WizardLogger::warning("Paquet de résolution de login reçu");
                                          break;
        case Packet::DISCONNECT_ID :      manageDisconnectRequest(player, customPacket);
                                          break;
        /* Card process */
        case Packet::CARTE_INFO_ID :      WizardLogger::warning("Paquet d'info de carte reçu");
                                          break;
        case Packet::CARTE_IMG_REQ_ID :   manageCardImgRequest(player, (Packet::intPacket*) customPacket);
                                          break;
        case Packet::CARTE_IMG_ID :       WizardLogger::warning("Paquet d'image reçu");
                                          break;
        /* Tchat process */
        case Packet::TCHAT_SEND_MSG_ID :  playerSendMsg(player, (Packet::tchatSendMsgPacket*) customPacket);
                                          break;
        case Packet::TCHAT_RECEV_MSG_ID : WizardLogger::info("Message de tchat reçu");
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
        case Packet::ASK_DECK_AND_PSEUDO_ID :
                                          WizardLogger::warning("Paquet d'initialisation de la partie reçu");
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
        case Packet::C_PLACE_CARD_ID:     managePlaceCard(player, (Packet::intPacket*) customPacket);
                                          break;
        case Packet::C_PLACE_CARD_MAKE_SPELL_ID:
                                          managePlaceAttackCard(player, (Packet::twoCardPacket*) customPacket);
                                          break;
        case Packet::S_ATTACK_ID:         WizardLogger::warning("Packet d'attack d'une carte (serveur)");
                                          break;
        case Packet::S_PLACE_SPELL_ID:    WizardLogger::warning("Packet pour poser une carte sort (serveur)");
                                          break;
        case Packet::S_PLACE_CARD_ID:     WizardLogger::warning("Packet pour poser une carte (serveur)");
                                          break;
        case Packet::S_PLACE_CARD_AND_ATTACK_ID:
                                          WizardLogger::warning("Packet pour poser une carte et attaquer (serveur)");
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

void PacketManager::manageCardImgRequest(Player* player, Packet::intPacket* cardRequest) {
    //TODO get card form server database and call sendCardImg (block client recev :/)
}

/**
 * Send all card's info to the client
 *
 * @param player : the player who to send this packet
 * @param card : the card's info needed
 */
void PacketManager::sendCardInfo(Player* player, Card* card) {
    WizardLogger::info("Envoie d'information concernant la carte: " +
                       std::to_string(card->getId()));
    Packet::cardInfosPacket* cardPacket = new Packet::cardInfosPacket();

    cardPacket->data.monster = false; // default
    cardPacket->data.carteID = card->getId();
    for(unsigned i = 0; i < MAX_CARD_NAME; ++i) {
        if(i < card->getName().size()) {
            cardPacket->data.name[i] = card->getName()[i];
        } else {
            cardPacket->data.name[i] = ' ';
        }
    }
    for(unsigned i = 0; i < MAX_DESCRITION_SIZE; ++i) cardPacket->data.description[i] = ' ';
    cardPacket->data.energyCost = card->getEnergyCost();
    if(card->isMonster()) {
        CardMonster* monsterCard = static_cast<CardMonster*>(card);
        cardPacket->data.monster = true;
        cardPacket->data.attack = monsterCard->getAttack();
        cardPacket->data.maxHP = monsterCard->getMaxLife();
    }

    /* Send and free */
    player->sendPacket((Packet::packet*) cardPacket, sizeof(*cardPacket));
    delete cardPacket;
}


/* Send card img to the client
 * @param player : the player who to send this packet
 * @param card : the card's img needed
 */
void PacketManager::sendCardImg(Player* player, Card* card) {
    //TODO send card img to the client
}

//============================TCHAT PROCESS===========================================

void PacketManager::playerSendMsg(Player* player, const Packet::tchatSendMsgPacket* msgPacket) {

    // Get adverse pseudo
    std::string playerTo = "";
    int i = 0;
    while(i < MAX_PSEUDO_SIZE && msgPacket->pseudoTo[i] != ' ') {
        playerTo += msgPacket->pseudoTo[i];
        ++i;
    }

    Player* play = PlayerManager::findPlayerByName(playerTo);
    if(play != nullptr) { // Verify that he is friends
        // Get message
        std::string msg(msgPacket->msg);

        WizardLogger::info("Message de: " + player->getName() + " vers: " +
                           playerTo + " => " + msg);

        std::string playerFrom = player->getName();
        sendPlayerRecdvMsg(player, playerFrom, playerTo, msg);
        sendPlayerRecdvMsg(play, playerFrom, playerTo, msg);
    } else {
        WizardLogger::warning("Message à un joueur déconnecté: " + playerTo);
    }
}

void PacketManager::sendPlayerRecdvMsg(Player* player, std::string playerFrom,
                                       std::string playerTo, std::string message) {

    Packet::tchatRecevMsgPacket* tchatPacket = new Packet::tchatRecevMsgPacket();


    for (int i = 0; i < MESSAGES_MAX_SIZE; ++i) {
        if(i < message.size()) {
            tchatPacket->msg[i] = message[i];
        } else {
            tchatPacket->msg[i] = ' ';
        }
    }

    for (int i = 0; i < MAX_PSEUDO_SIZE; ++i) {
        if(i < playerTo.size()) {
            tchatPacket->pseudoTo[i] = playerTo[i];
        } else {
            tchatPacket->pseudoTo[i] = ' ';
        }
    }


    for (int i = 0; i < MAX_PSEUDO_SIZE; ++i) {
        if(i < playerFrom.size()) {
            tchatPacket->pseudoFrom[i] = playerFrom[i];
        } else {
            tchatPacket->pseudoFrom[i] = ' ';
        }
    }


    /* Send and free */
    player->sendPacket((Packet::packet*) tchatPacket, sizeof(*tchatPacket));
    delete tchatPacket;
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
void PacketManager::askDeck(Player *player, std::string ennemyPseudo) {
    WizardLogger::info("Demande à : " + player->getName() +
                       " de choisir son deck");

    Packet::pseudoPacket *askDeckPacket = new Packet::pseudoPacket();

    /* Set ID and ennemy's pseudo */
    askDeckPacket->ID = Packet::ASK_DECK_AND_PSEUDO_ID;

    for (int i = 0 ; i < ennemyPseudo.size() ; ++i) askDeckPacket->pseudo[i] = ennemyPseudo[i];

    /* Send and free */
    player->sendPacket((Packet::packet*) askDeckPacket, sizeof(*askDeckPacket));
    delete askDeckPacket;
}


void PacketManager::manageDrop(Player* player, Packet::intPacket* dropIDPacket) {
    //TODO tell Game wich card is drop
}

void PacketManager::manageAttack(Player *player, Packet::twoCardPacket* attackPacket) {
    if(player->isPlayerInGame()) {
        PlayerInGame* pIG = static_cast<PlayerInGame*>(player);
        Error res = pIG->reqAttack(attackPacket->cardOne, attackPacket->cardTwo);
        if(res != Error::NoError) {
            sendError(player, res);
        }
    } else {
        WizardLogger::warning("ManageAttack appellé par un player et non un PlayerInGame");
    }
}

void PacketManager::managePlaceCard(Player* player, Packet::intPacket* placePacket) {
    if(player->isPlayerInGame()) {
        PlayerInGame* pIG = static_cast<PlayerInGame*>(player);
        Error res = pIG->reqPlaceCard(placePacket->data);
        if(res != Error::NoError) {
            sendError(player, res);
        }
    } else {
        WizardLogger::warning("ManagePlaceCard appellé par un player et non un PlayerInGame");
    }
}

void PacketManager::managePlaceAttackCard(Player* player, Packet::twoCardPacket* placeAttackPacket) {
    if(player->isPlayerInGame()) {
        PlayerInGame* pIG = static_cast<PlayerInGame*>(player);
        Error res = pIG->reqPlaceAttackCard(placeAttackPacket->cardOne, placeAttackPacket->cardTwo);
        if(res != Error::NoError) {
            sendError(player, res);
        }
    } else {
        WizardLogger::warning("ManagePlaceAttackCard appellé par un player et non un PlayerInGame");
    }
}


void PacketManager::manageEndTurn(Player* player, Packet::packet* packet) {
    if(player->isPlayerInGame()) {
        PlayerInGame* pIG = static_cast<PlayerInGame*>(player);
        pIG->reqEndTurn();

    } else {
        WizardLogger::warning("manageEndTurn appellé par un player et non un PlayerInGame");
    }
}

void PacketManager::manageQuitGame(Player* player, Packet::packet* packet) {
    //TODO tell Game about (rage) quit
}

/**
 * Send information to tell about the turn
 *
 * @param player who must recieve informations
 * @param nbrTurn during the begin of the game
 * @param isTurn is the player turn or not
 */
void PacketManager::sendTurnInfo(Player* player, unsigned nbrTurn, bool isTurn) {

    Packet::turnPacket *turnPacket =  new Packet::turnPacket();

    turnPacket->nbrTurn = nbrTurn;
    turnPacket->isTurn = isTurn;

    /* Send and free */
    player->sendPacket((Packet::packet*) turnPacket, sizeof(*turnPacket));
    delete turnPacket;

}

/**
 * Call when the game start
 *
 * @param player who must recev packet
 * @param listCard list of draw card
 */
void PacketManager::sendDrawBegin(Player* player, std::vector<unsigned> listCard) {
    Packet::beginDrawPacket *drawPacket = new Packet::beginDrawPacket();

    for(unsigned i = 0; i < MIN_CARD_IN_HAND; ++i) {
        drawPacket->listID[i] = listCard[i];
    }

    player->sendPacket((Packet::packet*) drawPacket, sizeof(*drawPacket));
    delete drawPacket;
}

/**
 * Send draw card to the player
 *
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
 * Send information to the player that adverse player have
 * draw a card
 *
 * @param player who will reciev the packet
 */
void PacketManager::sendAdverseDraw(Player* player) {
    Packet::packet *advDrawPacket = new Packet::packet();

    advDrawPacket->ID = Packet::ADVERSE_DRAW_ID;

    /* Send and free */
    player->sendPacket((Packet::packet*) advDrawPacket, sizeof(*advDrawPacket));
    delete advDrawPacket;
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
 * @param targetPosition position of the card wich have dammage (-1 for adverse player)
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


    Packet::placeAttackPacket* placeAttackPacket = new Packet::placeAttackPacket();

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
 * Call when card spell is placed
 *
 * @param player player who must recieve information
 * @param pseudo of the player who place
 * @param cardID wich is placed
 * @param cardPosition position of the new card
 * @param targetPosition position of the attack card
 * @param heal of the target card
 */
void PacketManager::sendPlaceSpellCard(Player* player, std::string pseudo, int cardID,
                                       int targetPosition, unsigned heal) {

    Packet::placeAttackSpellPacket* placeAttackSpellPacket = new Packet::placeAttackSpellPacket();

    for (int i = 0 ; i < pseudo.size() ; ++i) placeAttackSpellPacket->data.pseudo[i] = pseudo[i];
    placeAttackSpellPacket->data.idCard = cardID;
    placeAttackSpellPacket->data.targetPosition = targetPosition;
    placeAttackSpellPacket->data.heal = heal;

    // Send and free
    player->sendPacket((Packet::packet*) placeAttackSpellPacket, sizeof(*placeAttackSpellPacket));
    delete placeAttackSpellPacket;

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
 * Send the MAX_PLAYER_CLASSEMENT best player stats
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


//====================================== ERROR ========================================

/**
 * Send an error code
 *
 * @param error which must be send
 */
void PacketManager::sendError(Player* player, Error error) {
    Packet::intPacket* errorPacket = new Packet::intPacket();

    errorPacket->ID = Packet::ERROR_ID;
    errorPacket->data = error;

    /* Send and free */
    player->sendPacket((Packet::packet*) errorPacket, sizeof(*errorPacket));
    delete errorPacket;
}

