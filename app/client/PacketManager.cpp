#include "PacketManager.hpp"

extern Connection *conn;
extern CacheManager *cacheManager;

void PacketManager::managePacket(Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {

        /* Login process */
        case Packet::LOGIN_REQ_ID :       WizardLogger::warning("Paquet de requête de login reçu");
                                          break;
        case Packet::REGIST_REQ_ID :      WizardLogger::warning("Paquet de requête d'inscription reçu");
                                          break;
        case Packet::LOGIN_RES_ID :       loginResult((Packet::intPacket*) customPacket);
                                          break;

        /* Recieve player informations */
        case Packet::PLAYER_INFO_ID :     playerInfo((Packet::playerInfoPacket*) customPacket);
                                          break;
        case Packet::DISCONNECT_ID :      WizardLogger::warning("Paquet de déconnection reçu");
                                          break;

        /* Card process */
        case Packet::CARTE_REQ_ID :       WizardLogger::warning("Paquet de requête de carte reçu");
                                          break;
        case Packet::CARTE_INFO_ID :      saveCardInfo((Packet::cardInfosPacket*) customPacket);
                                          break;
        case Packet::CARTE_IMG_REQ_ID :   WizardLogger::warning("Paquet de requête d'image de carte reçu");
                                          break;
        case Packet::CARTE_IMG_ID :       saveCardImg((Packet::cardImgPacket*) customPacket);
                                          break;

        /* Tchat process */
        case Packet::TCHAT_CONV_REQ_ID :  WizardLogger::warning("Paquet de nouvelle conversation (tchat) reçu");
                                          break;
        case Packet::TCHAT_NEW_CONV_ID :  startNewConv((Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::TCHAT_MESSAGE_ID :   getMessage((Packet::tchatMessagePacket*) customPacket);
                                          break;
        case Packet::TCHAT_END_REQ_ID :   WizardLogger::warning("Paquet de fin de conversation (tchat) reçu");
                                          break;
        case Packet::TCHAT_END_CONV_ID :  stopConv((Packet::pseudoPacket*) customPacket);
                                          break;

        /* Friend process */
        case Packet::FRIEND_ADD_ID :      WizardLogger::warning("Paquet d'ajout d'ami reçu");
                                          break;
        case Packet::FRIEND_DEL_ID :      removeFriend((Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::FRIENDS_REQ_ID :     requestFriend((Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::FRIENDS_LIST_REQ_ID :WizardLogger::warning("Paquet de requête de liste d'ami reçu");
                                          break;
        case Packet::FRIENDS_LIST_ID :    updateFriendList((Packet::friendListPacket*) customPacket);
                                          break;

        /* Launching game process */
        case Packet::WAITING_ID :         WizardLogger::warning("Paquet d'attende de partie reçu");
                                          break;
        case Packet::CANCEL_ID :          WizardLogger::warning("Paquet d'annulation de partie reçu");
                                          break;
        case Packet::ASK_DECK_ID :        wizardDisplay->askDeck();
                                          break;
        case Packet::GAME_START_ID:       startGame((Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::DECK_CHOOS_ID :      WizardLogger::warning("Paquet de choix de deck reçu");
                                          break;

        /* Game process */
        case Packet::TURN_ID :            setTurn((Packet::turnPacket*) customPacket);
                                          break;
        case Packet::DRAW_ID :            setDraw((Packet::intPacket*) customPacket);
                                          break;
        case Packet::ASK_DROP_ID :        askDrop((Packet::intPacket*) customPacket);
                                          break;
        case Packet::DROP_ID :            WizardLogger::warning("Paquet de drop reçu");
                                          break;
        case Packet::C_ATTACK_ID:         WizardLogger::warning("Packet d'attack d'une carte (client)");
                                          break;
        case Packet::C_PLACE_CARD_ID:     WizardLogger::warning("Packet pour poser une carte (client)");
                                          break;
        case Packet::C_PLACE_SPELL_ID:    WizardLogger::warning("Packet pour poser une carte sort (client)");
                                          break;
        case Packet::C_PLACE_CARD_MAKE_SPELL_ID:
                                          WizardLogger::warning("Packet pour une carte placé avec un effet (client)");
                                          break;
        case Packet::S_ATTACK_ID:         manageAttack((Packet::attackPacket*) customPacket);
                                          break;
        case Packet::S_PLACE_SPELL_ID:    managePlaceSpell((Packet::placeAttackSpellPacket*) customPacket);
                                          break;
        case Packet::S_PLACE_CARD_ID:     managePlaceCard((Packet::placeCardPacket*) customPacket);
                                          break;
        case Packet::S_PLACE_CARD_AND_ATTACK_ID:
                                          managePlaceCardAttack((Packet::placeAttackPacket*) customPacket);
        case Packet::END_TURN_ID :        WizardLogger::warning("Paquet de fin de tour reçu");
                                          break;
        case Packet::QUIT_ID :            WizardLogger::warning("Paquet de fin de partie (quit) reçu");
                                          break;
        case Packet::END_GAME_ID :        manageEndGame((Packet::endGamePacket*) customPacket);
                                          break;
        default :                         WizardLogger::warning("Paquet inconnue reçu: " + customPacket->ID);
                                          break;
    }
}

//===========================LOGIN PROCESS===========================================

void PacketManager::loginResult(const Packet::intPacket* resultPacket) {
    /* Check if size is correct to detect corrupted packet */
    if (resultPacket->size != sizeof(int)) {
        WizardLogger::error("Paquet de résultat de login corrompu reçu ("
        +std::to_string(resultPacket->size)+"/"+std::to_string(sizeof(int))+")");
    }

    wizardDisplay->displayLoginResult("Erreur durant le login");
}

void PacketManager::playerInfo(const Packet::playerInfoPacket* playerPacket) {
    WizardLogger::info(playerPacket->data.pseudo);
    WizardLogger::info(std::to_string(playerPacket->data.victories));
    WizardLogger::info(std::to_string(playerPacket->data.defeats));

    std::string pseudo = playerPacket->data.pseudo;
    unsigned* collection = const_cast<unsigned*>(playerPacket->data.collection);
    char* charDecks = const_cast<char*>(playerPacket->data.decks);
    std::vector<std::string> decks;
    for(unsigned nbrDeck = 0; nbrDeck < MAX_DECKS; ++nbrDeck) {
        std::string current = "";
        unsigned positionStart = nbrDeck*MAX_DECK_NAME;

        for(unsigned i = 0; i < MAX_DECK_NAME && charDecks[positionStart+i] != ' '; ++i) {
            current += charDecks[positionStart+i];
        }

        if(current != "") {
            decks.push_back(current);
            WizardLogger::info("Lecture de: " + current);
        }
    }
    WizardLogger::info("Nombre de deck: " + std::to_string(decks.size()));

    // TO DO: vérifier que tout est bon
    std::string friends[MAX_FRIENDS];
    for(unsigned nbrAmi = 0; nbrAmi < MAX_FRIENDS; ++nbrAmi) {
        std::string current = "";
        for(unsigned i = 0; i < MAX_PSEUDO_SIZE; ++i) {
            current+= playerPacket->data.friendsList[nbrAmi*MAX_PSEUDO_SIZE+i];
        }
        friends[nbrAmi] = current;
    }

    unsigned victories = playerPacket->data.victories;
    unsigned defeats = playerPacket->data.defeats;

    new Player(pseudo, collection, decks, friends, victories, defeats);

    wizardDisplay->valideLogin();
}

/**
 * Send a login request to the server
 *
 * @param pseudo : pseudo array of the user
 * @param password : password array of the user
 */
void PacketManager::makeLoginRequest(const char *pseudo, const char *password) {
    /* Create and complete a new loginPacket */
    Packet::loginRequestPacket *loginPacket = new Packet::loginRequestPacket();
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        loginPacket->pseudo[i] = pseudo[i];
    }
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        loginPacket->password[i] = password[i];
    }
    
    /* Send it to the server */
    conn->sendPacket((Packet::packet*) loginPacket, sizeof(*loginPacket));
    
    /* Clean memory */
    delete loginPacket;
}

/**
 * Send a login request to the server
 *
 * @param pseudo : pseudo array of the user
 * @param password : password array of the user
 */
void PacketManager::makeRegistrationRequest(const char *pseudo, const char *password) {
    /* Create and complete a new loginPacket and modify ID to match registration request */
    Packet::loginRequestPacket *registrationPacket = new Packet::loginRequestPacket();
    registrationPacket->ID = Packet::REGIST_REQ_ID;
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        registrationPacket->pseudo[i] = pseudo[i];
    }
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        registrationPacket->password[i] = password[i];
    }
    
    /* Send it to the server */
    conn->sendPacket((Packet::packet*) registrationPacket, sizeof(*registrationPacket));
    
    /* Clean memory */
    delete registrationPacket;
}

/**
 * Send a disconnection signal to the server (help detect crash)
 */
void PacketManager::sendDisconnection() {
    /* Create and specify a new logoutPacket */
    Packet::packet *logoutPacket = new Packet::packet();
    logoutPacket->ID = Packet::DISCONNECT_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet::packet*) logoutPacket, sizeof(*logoutPacket));
    
    /* Clean memory */
    delete logoutPacket;
}

//============================CARD PROCESS===========================================

void PacketManager::saveCardInfo(const Packet::cardInfosPacket* cardPacket) {
    Card *newCard = new Card(cardPacket->data.carteID, cardPacket->data.monster, std::string(cardPacket->data.name),
    std::string(cardPacket->data.description), cardPacket->data.energyCost, cardPacket->data.maxHP);
    cacheManager->addToCache(newCard);
}

void PacketManager::saveCardImg(const Packet::cardImgPacket* cardImgPacket) {
    //TODO save to file
}

/**
 * Request card's information
 *
 * @param ID : the card's ID
 */
void PacketManager::makeCardRequest(const unsigned ID) {
    Packet::intPacket *cardReqPacket = new Packet::intPacket();
    
    /* Set ID and ID */
    cardReqPacket->ID = Packet::CARTE_REQ_ID;
    cardReqPacket->data = ID;
    
    /* Send and free */
    conn->sendPacket((Packet::packet*) cardReqPacket, sizeof(*cardReqPacket));
    delete cardReqPacket;
}

/**
 * Request card's picture
 *
 * @param ID : the card's ID
 */
void PacketManager::makeCardImgRequest(const unsigned ID) {
    Packet::intPacket *cardImgReqPacket = new Packet::intPacket();
    
    /* Set ID and ID */
    cardImgReqPacket->ID = Packet::CARTE_IMG_REQ_ID;
    cardImgReqPacket->data = ID;
    
    /* Send and free */
    conn->sendPacket((Packet::packet*) cardImgReqPacket, sizeof(*cardImgReqPacket));
    delete cardImgReqPacket;
}

//============================TCHAT PROCESS===========================================

void PacketManager::startNewConv(const Packet::pseudoPacket* newConvPacket) {
    //TODO start new conversation
}

void PacketManager::getMessage(const Packet::tchatMessagePacket* messagePacket) {
    //TODO display message
}

void PacketManager::stopConv(const Packet::pseudoPacket* endConvPacket) {
    //TODO stop a conversation
}

/**
 * Ask to start a new conversation with someone
 *
 * @param pseudo : other player's pseudo
 */
void PacketManager::makeTchatRequest(const std::string pseudo) {
    Packet::pseudoPacket *newConvReq = new Packet::pseudoPacket();
    
    /* Set ID and pseudo */
    newConvReq->ID = Packet::TCHAT_CONV_REQ_ID;
    for (int i = 0 ; i < pseudo.size() ; ++i) newConvReq->pseudo[i] = pseudo[i];
    
    /* Send and free */
    conn->sendPacket((Packet::packet*) newConvReq, sizeof(*newConvReq));
    delete newConvReq;
}


/**
 * Send a message to someone
 *
 * @param message : the message to send
 */
void PacketManager::sendMessage(const std::string message) {
    Packet::tchatMessagePacket *messagePacket = new Packet::tchatMessagePacket();
    
    /* Set message */
    for (int i = 0 ; i < message.size() ; ++i) messagePacket->msg[i] = message[i];
    
    /* Send and free */
    conn->sendPacket((Packet::packet*) messagePacket, sizeof(*messagePacket));
    delete messagePacket;
}


/**
 * Ask to stop a conversation with someone
 *
 * @param pseudo : other player's pseudo
 */
void PacketManager::makeTchatStopRequest(const std::string pseudo) {
    Packet::pseudoPacket *stopConvReq = new Packet::pseudoPacket();
    
    /* Set ID and pseudo */
    stopConvReq->ID = Packet::TCHAT_END_REQ_ID;
    for (int i = 0 ; i < pseudo.size() ; ++i) stopConvReq->pseudo[i] = pseudo[i];
    
    /* Send and free */
    conn->sendPacket((Packet::packet*) stopConvReq, sizeof(*stopConvReq));
    delete stopConvReq;
}

//============================FRIEND PROCESS===========================================

void PacketManager::removeFriend(const Packet::pseudoPacket* removeFriendPacket) {
    //TODO remove friend from friend list
}

void PacketManager::requestFriend(const Packet::pseudoPacket* friendRequestPacket) {
    //TODO ask if user want to be friend
}

void PacketManager::updateFriendList(const Packet::friendListPacket* friendListPacket) {
    //TODO update friend list
}

/**
 * Send a friend request
 *
 * @param pseudo : other player's pseudo
 */
void PacketManager::makeFriendRequest(const char* pseudo) {
    Packet::pseudoPacket *friendReq = new Packet::pseudoPacket();
    
    /* Set ID and pseudo */
    friendReq->ID = Packet::FRIEND_ADD_ID;
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) friendReq->pseudo[i] = pseudo[i];
    
    /* Send and free */
    conn->sendPacket((Packet::packet*) friendReq, sizeof(*friendReq));
    delete friendReq;
}

/**
 * Ask for friend list update
 */
void PacketManager::makeFriendListRequest() {
    /* Create and specify a new logoutPacket */
    Packet::packet *friendListReq = new Packet::packet();
    friendListReq->ID = Packet::FRIENDS_LIST_REQ_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet::packet*) friendListReq, sizeof(*friendListReq));
    
    /* Clean memory */
    delete friendListReq;
}

//============================LAUNCHING PROCESS=========================================

void PacketManager::startGame(const Packet::pseudoPacket* packet) {
    wizardDisplay->launchGame(packet->pseudo);
}


/**
 * Inform server we are ready and wainting for party
 */
void PacketManager::makeGameRequest() {
    /* Create and specify a new logoutPacket */
    Packet::packet *gameReq = new Packet::packet();
    gameReq->ID = Packet::WAITING_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet::packet*) gameReq, sizeof(*gameReq));
    
    /* Clean memory */
    delete gameReq;
}

/**
 * Inform server thant we wont anymore play
 */
void PacketManager::makeGameCancelRequest() {
    /* Create and specify a new logoutPacket */
    Packet::packet *cancelInfo = new Packet::packet();
    cancelInfo->ID = Packet::CANCEL_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet::packet*) cancelInfo, sizeof(*cancelInfo));
    
    /* Clean memory */
    delete cancelInfo;
}

void PacketManager::sendSelectedDeck(const char* deck) {
    Packet::deckPacket *sendChoosenDeck = new Packet::deckPacket();
    
    /* Set ID and ID */
    sendChoosenDeck->ID = Packet::DECK_CHOOS_ID;
    for (int i = 0 ; i < MAX_DECK_NAME; ++i) sendChoosenDeck->deck[i] = deck[i];
    
    /* Send and free */
    conn->sendPacket((Packet::packet*) sendChoosenDeck, sizeof(*sendChoosenDeck));
    delete sendChoosenDeck;
}

//==============================GAME PROCESS============================================

void PacketManager::setTurn(const Packet::turnPacket* turnPacket) {
    //TODO update in-game info and inform if it's our turn
}

void PacketManager::setDraw(const Packet::intPacket* drawPacket) {
    //TODO update in-game hand (and deck)
}

void PacketManager::askDrop(const Packet::intPacket* askDropPacket) {
    //TODO ask to trash a certain amount
}

//void PacketManager::manageAttack(const Packet::attackPacket* attackPacket) {
//    bool adverse = (Player::getPlayer()->getName() == attackPacket->data.pseudo);

//    if(attackPacket->data.isNewCard) {
//        wizardDisplay->placeCard(adverse, attackPacket->data.ID);
//    }

//    wizardDisplay->attackCard(adverse, attackPacket->data.ID, attackPacket->data.target,
//                              attackPacket->data.isEffect, attackPacket->data.finalLife);

//}

//void PacketManager::manageSpell(const Packet::attackPacket* spellPacket) {
//    //TODO update in-game info with a spell
//}


void PacketManager::manageAttack(Packet::attackPacket* attackPacket) {

}

void PacketManager::managePlaceSpell(Packet::placeAttackSpellPacket* placeAttackSpellPacket) {

}

void PacketManager::managePlaceCard(Packet::placeCardPacket* placeCardPacket) {

}

void PacketManager::managePlaceCardAttack(Packet::placeAttackPacket* placeAttackPacket) {

}


void PacketManager::manageEndGame(const Packet::endGamePacket* endPacket) {
    //TODO tell if we win and display winner's new card
}

/**
 * Inform server to trash a card
 *
 * @param ID : the card's ID
 */
void PacketManager::sendDrop(const int ID) {
    Packet::intPacket *dropCard = new Packet::intPacket();
    
    /* Set ID and ID */
    dropCard->ID = Packet::DROP_ID;
    dropCard->data = ID;
    
    /* Send and free */
    conn->sendPacket((Packet::packet*) dropCard, sizeof(*dropCard));
    delete dropCard;
}

/**
 * Inform server for an attack attempt
 * @param from : ID of card doing attack
 * @param target : ID of the target's card (or -1 for player)
 */
//void PacketManager::sendAttack(const int from, const int target) {
//    Packet::attackPacket *attackPacket = new Packet::attackPacket();
    
//    /* Set ID and info (server fix pseudo and finalLife) */
//    attackPacket->ID = Packet::ATTACK_ID;
//    attackPacket->data.ID = from;
//    attackPacket->data.target = target;
    
//    /* Send and free */
//    conn->sendPacket((Packet::packet*) attackPacket, sizeof(*attackPacket));
//    delete attackPacket;
//}

/**
 * Inform server for an attack attempt
 * @param from : ID of card doing attack
 * @param target : ID of the target's card (or -1 for player)
 */
//void PacketManager::sendAttack(const int from, const int target) {
//    Packet::attackPacket *attackPacket = new Packet::attackPacket();

//    /* Set ID and info (server fix pseudo and finalLife) */
//    attackPacket->ID = Packet::ATTACK_ID;
//    attackPacket->data.ID = from;
//    attackPacket->data.target = target;

//    /* Send and free */
//    conn->sendPacket((Packet::packet*) attackPacket, sizeof(*attackPacket));
//    delete attackPacket;
//}


/**
 * Inform server for a spell attempt
 * @param from : ID of card doing spell
 * @param target : ID of the target's card (or -1 for player)
 */
//void PacketManager::sendSpell(const int from, const int target) {
//    Packet::attackPacket *spellPacket = new Packet::attackPacket();
    
//    /* Set ID and info (server fix pseudo and finalLife) */
//    spellPacket->ID = Packet::SPELL_ID;
//    spellPacket->data.ID = from;
//    spellPacket->data.target = target;
    
//    /* Send and free */
//    conn->sendPacket((Packet::packet*) spellPacket, sizeof(*spellPacket));
//    delete spellPacket;
//}

/**
 * Inform server that we have finish our turn
 */
void PacketManager::endTurn() {
    /* Create and specify a new logoutPacket */
    Packet::packet *endTurn = new Packet::packet();
    endTurn->ID = Packet::END_TURN_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet::packet*) endTurn, sizeof(*endTurn));
    
    /* Clean memory */
    delete endTurn;
}

/**
 * Inform server that we (rage) quit party and we loose
 */
void PacketManager::quit() {
    /* Create and specify a new logoutPacket */
    Packet::packet *quit = new Packet::packet();
    quit->ID = Packet::QUIT_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet::packet*) quit, sizeof(*quit));
    
    /* Clean memory */
    delete quit;
}

