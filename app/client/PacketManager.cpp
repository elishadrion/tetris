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
        case Packet::LOGIN_COMPLETE_ID :  loginComplete(customPacket);
                                          break;

        /* Recieve player informations */
        case Packet::PLAYER_INFO_ID :     playerInfo((Packet::playerInfoPacket*) customPacket);
                                          break;
        case Packet::DISCONNECT_ID :      WizardLogger::warning("Paquet de déconnection reçu");
                                          break;

        /* Card process */
        case Packet::CARTE_INFO_ID :      saveCardInfo((Packet::cardInfosPacket*) customPacket);
                                          break;
        case Packet::CARTE_IMG_REQ_ID :   WizardLogger::warning("Paquet de requête d'image de carte reçu");
                                          break;
        case Packet::CARTE_IMG_ID :       saveCardImg((Packet::cardImgPacket*) customPacket);
                                          break;

        /* Tchat process */
        case Packet::TCHAT_RECEV_MSG_ID:  getMessage((Packet::tchatRecevMsgPacket*) customPacket);
                                          break;
        case Packet::TCHAT_SEND_MSG_ID :  WizardLogger::info("Message de tchat reçu");
                                          break;

        /* Friend process */
        case Packet::FRIEND_ADD_ID :      WizardLogger::warning("Paquet d'ajout d'ami reçu");
                                          break;
        case Packet::FRIEND_DEL_ID :      removeFriend((Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::FRIENDS_REQ_ID :     requestFriend((Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::FRIENDS_LIST_REQ_ID: WizardLogger::warning("Paquet de requête de liste d'ami reçu");
                                          break;
        case Packet::FRIENDS_LIST_ID :    updateFriendList((Packet::friendListPacket*) customPacket);
                                          break;

        // Classement
        case Packet::SEND_CLASSEMENT_ID:  manageClassement((Packet::classementPacket*) customPacket);
                                          break;

        /* Launching game process */
        case Packet::WAITING_ID :         WizardLogger::warning("Paquet d'attende de partie reçu");
                                          break;
        case Packet::CANCEL_ID :          WizardLogger::warning("Paquet d'annulation de partie reçu");
                                          break;
        case Packet::ASK_DECK_AND_PSEUDO_ID:
                                          askDeckAndPseudo((Packet::pseudoPacket*) customPacket);
                                          break;
        case Packet::DECK_CHOOS_ID :      WizardLogger::warning("Paquet de choix de deck reçu");
                                          break;

        /* Game process */
        case Packet::TURN_ID :            setTurn((Packet::turnPacket*) customPacket);
                                          break;
        case Packet::BEGIN_DRAW_ID:       setBeginDraw((Packet::beginDrawPacket*) customPacket);
                                          break;
        case Packet::DRAW_ID :            setDraw((Packet::intPacket*) customPacket);
                                          break;
        case Packet::ADVERSE_DRAW_ID:     wizardDisplay->adverseDrawCard();
                                          break;
        case Packet::ASK_DROP_ID :        askDrop((Packet::intPacket*) customPacket);
                                          break;
        case Packet::DROP_ID :            WizardLogger::warning("Paquet de drop reçu");
                                          break;
        case Packet::C_ATTACK_ID:         WizardLogger::warning("Packet d'attack d'une carte (client)");
                                          break;
        case Packet::C_PLACE_CARD_ID:     WizardLogger::warning("Packet pour poser une carte (client)");
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
        case Packet::ERROR_ID:            manageError((Packet::intPacket*) customPacket);
                                          break;
        default :                         WizardLogger::warning("Paquet inconnue reçu: " +
                                                            std::to_string(customPacket->ID));
                                          break;
    }
}

//===========================LOGIN PROCESS===========================================

void PacketManager::loginResult(const Packet::intPacket* resultPacket) {
    /* Check if size is correct to detect corrupted packet */
    if (resultPacket->size != sizeof(int)) {
        WizardLogger::error("Paquet de résultat de login corrompu reçu (" +
                            std::to_string(resultPacket->size) + "/" +
                            std::to_string(sizeof(int))+")");
    }
    
    /* Lock, signal other thread and unlock */
    pthread_mutex_lock(&wizardDisplay->packetStackMutex);
    wizardDisplay->packetStack.push_back(reinterpret_cast<void*>(new std::string("Erreur durant le login")));
    pthread_cond_broadcast(&wizardDisplay->packetStackCond);
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);
}

void PacketManager::playerInfo(const Packet::playerInfoPacket* playerPacket) {
    WizardLogger::info(playerPacket->data.pseudo);
    WizardLogger::info("victoire" + std::to_string(playerPacket->data.victories));
    WizardLogger::info("défaite: " + std::to_string(playerPacket->data.defeats));

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
    
    /* Lock, signal other thread and unlock */
    pthread_mutex_lock(&wizardDisplay->packetStackMutex);
    pthread_cond_broadcast(&wizardDisplay->packetStackCond);
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);
}

void PacketManager::loginComplete(const Packet::packet* packet) {
    WizardLogger::info("Fin du chargement. Nombre de cartes: " +
                       CacheManager::getNbrCard());
    /* Lock, signal other thread and unlock */
    pthread_mutex_lock(&wizardDisplay->packetStackMutex);
    pthread_cond_broadcast(&wizardDisplay->packetStackCond);
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);
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
    WizardLogger::info("Récepetion de la carte: " + std::to_string(cardPacket->data.carteID));
    std::string name(cardPacket->data.name);
    std::string desc(cardPacket->data.description);
    //TODO only remove space after name and desc
    name.erase(remove_if(name.begin(), name.end(), isspace), name.end());
    desc.erase(remove_if(desc.begin(), desc.end(), isspace), desc.end());
    Card *newCard = new Card(cardPacket->data.carteID, cardPacket->data.monster, name, desc, cardPacket->data.energyCost,
                             cardPacket->data.maxHP, cardPacket->data.attack);

    cacheManager->addCard(newCard);
    
    /* Send confirmation */
    Packet::packet *packet = new Packet::packet();
    conn->sendPacket(packet, sizeof(*packet));
    delete packet;
}

void PacketManager::saveCardImg(const Packet::cardImgPacket* cardImgPacket) {
    //TODO save to file
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

void PacketManager::getMessage(const Packet::tchatRecevMsgPacket* messagePacket) {
    int i;

    std::string pseudoFrom = "";
    i = 0;
    while(i < MAX_PSEUDO_SIZE && messagePacket->pseudoFrom[i] != ' ') {
        pseudoFrom += messagePacket->pseudoFrom[i];
        ++i;
    }

    std::string pseudoTo = "";
    i = 0;
    while(i < MAX_PSEUDO_SIZE && messagePacket->pseudoTo[i] != ' ') {
        pseudoTo += messagePacket->pseudoTo[i];
        ++i;
    }

    std::string finalMsg = "";
    std::string current = "";
    for(int j = 0; j < MESSAGES_MAX_SIZE; ++j) {
        char elem = messagePacket->msg[j];
        if(elem != ' ') {
            finalMsg += current;
            current = "";
            finalMsg += elem;
        } else {
            current += elem;
        }
    }

    wizardDisplay->recevTchatMsg(pseudoFrom, pseudoTo, finalMsg);
}

void PacketManager::sendMessage(const std::string toPlayer, const std::string message) {
    Packet::tchatSendMsgPacket *tchatPacket = new Packet::tchatSendMsgPacket();

    for (int i = 0; i < MESSAGES_MAX_SIZE; ++i) {
        if(i < message.size()) {
            tchatPacket->msg[i] = message[i];
        } else {
            tchatPacket->msg[i] = ' ';
        }
    }

    for (int i = 0; i < MAX_PSEUDO_SIZE; ++i) {
        if(i < toPlayer.size()) {
            tchatPacket->pseudoTo[i] = toPlayer[i];
        } else {
            tchatPacket->pseudoTo[i] = ' ';
        }
    }


    /* Send and free */
    conn->sendPacket((Packet::packet*) tchatPacket, sizeof(*tchatPacket));
    delete tchatPacket;
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


//============================== CLASSEMENT ============================================

void PacketManager::manageClassement(Packet::classementPacket* classementPacket) {
    int nbrPlayer = 0;
    std::string pseudo;
    do {
        // Pseudo //
        pseudo = "";
        int current = nbrPlayer*MAX_PSEUDO_SIZE;
        int i = 0;
        char elem = classementPacket->data.pseudo[current+i];
        while(i < MAX_PSEUDO_SIZE && elem != ' ') {
            pseudo += elem;
            ++i;
            elem = classementPacket->data.pseudo[current+i];
        }

        if(pseudo != "") {
            CacheManager::addPseudoRanking(new std::string(pseudo));

            // victoire //
            CacheManager::addVictoryRanking(classementPacket->data.victories[nbrPlayer]);

            // defeats //
            CacheManager::addDefeatRanking(classementPacket->data.defeats[nbrPlayer]);
        }

        ++nbrPlayer;

    } while(nbrPlayer < MAX_PLAYER_CLASSEMENT && pseudo != "");


    pthread_mutex_lock(&wizardDisplay->packetStackMutex);
    pthread_cond_broadcast(&wizardDisplay->packetStackCond);
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);
}

void PacketManager::askClassement() {
    Packet::packet *askClassement = new Packet::packet();
    askClassement->ID = Packet::ASK_CLASSEMENT_ID;

    // Send
    conn->sendPacket(askClassement, sizeof(*askClassement));
    // Memory
    delete askClassement;
}


//============================LAUNCHING PROCESS=========================================

void PacketManager::askDeckAndPseudo(const Packet::pseudoPacket* packet) {
    new GameManager(packet->pseudo);
    wizardDisplay->askDeck();
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
    WizardLogger::info("Récepetion d'une information sur le tour");
    GameManager::getInstance()->setTurn(turnPacket->nbrTurn, turnPacket->isTurn);
}

/**
 * Call when the game begin.  This packet inform of the inHand card
 *
 * @param drawPacket packet
 */
void PacketManager::setBeginDraw(const Packet::beginDrawPacket* drawPacket) {
    WizardLogger::info("Récepetion des cartes piochées");
    for(int i = 0; i < drawPacket->min_hand; ++i) {
        GameManager::getInstance()->drawCard(drawPacket->listID[i]);
        wizardDisplay->adverseDrawCard();
    }
    WizardLogger::info("Fin de la boucle parcourant les cartes piochées");
}

void PacketManager::setDraw(const Packet::intPacket* drawPacket) {
    WizardLogger::info("Récepetion de la carte piochée : " + std::to_string(drawPacket->data));
    
    GameManager::getInstance()->drawCard(drawPacket->data);
}

void PacketManager::askDrop(const Packet::intPacket* askDropPacket) {
    //TODO ask to trash a certain amount
}


/**
 * Call when a card is placed
 *
 * @param placeCardPacket the packet
 */
void PacketManager::managePlaceCard(Packet::placeCardPacket* placeCardPacket) {
    GameManager* gm = GameManager::getInstance();
    
    bool adverse = !(placeCardPacket->pseudo == Player::getPlayer()->getName());
    int cardId = placeCardPacket->idCard;
    unsigned position = placeCardPacket->cardPosition;

    if(gm->isTurn()) {
        gm->placeCard(cardId, position);

        /* Lock, signal other thread and unlock */
        pthread_mutex_lock(&wizardDisplay->packetStackMutex);
        pthread_cond_broadcast(&wizardDisplay->packetStackCond);
        pthread_mutex_unlock(&wizardDisplay->packetStackMutex);

    } else {
        if(adverse) {
            gm->ennemyPlaceCard(cardId, position);
        } else {
            WizardLogger::warning("Cela doit se faire avec les mutex");
        }
    }

}


/**
 * Call when a spell card is placed
 *
 * @param placeAttackSpellPacket the packet
 */
void PacketManager::managePlaceSpell(Packet::placeAttackSpellPacket* placeAttackSpellPacket) {
    GameManager* gm = GameManager::getInstance();

    int cardId = placeAttackSpellPacket->data.idCard;
    int targetPosition = placeAttackSpellPacket->data.targetPosition;
    unsigned heal = placeAttackSpellPacket->data.heal;


    if(placeAttackSpellPacket->data.pseudo == Player::getPlayer()->getName()) {
        gm->placeCardAndAttack(true, cardId, -1, targetPosition, heal);

        /* Lock, signal other thread and unlock */
        pthread_mutex_lock(&wizardDisplay->packetStackMutex);
        pthread_cond_broadcast(&wizardDisplay->packetStackCond);
        pthread_mutex_unlock(&wizardDisplay->packetStackMutex);

    } else {
        gm->placeAdverseCardAndAttack(true, cardId, -1, targetPosition, heal);
    }

}


/**
 * Call when an card attack an other
 *
 * @param attackPacket the packet
 */
void PacketManager::manageAttack(Packet::attackPacket* attackPacket) {
    GameManager* gm = GameManager::getInstance();

    bool adverse = !(attackPacket->data.pseudo == Player::getPlayer()->getName());
    unsigned cardPosition = attackPacket->data.cardPosition;
    int targetPosition = attackPacket->data.targetPosition;
    unsigned heal = attackPacket->data.heal;

    if(gm->isTurn()) {
        gm->attackCard(cardPosition, targetPosition, heal);

        /* Lock, signal other thread and unlock */
        pthread_mutex_lock(&wizardDisplay->packetStackMutex);
        pthread_cond_broadcast(&wizardDisplay->packetStackCond);
        pthread_mutex_unlock(&wizardDisplay->packetStackMutex);

    } else {
        if(adverse) {
            gm->adverseAttackCard(cardPosition, targetPosition, heal);
        } else {
            WizardLogger::warning("Cela doit se faire avec les mutex");
        }
    }

}


/**
 * Call when a card is placed and attack an other
 *
 * @param placeAttackPacket the packet
 */
void PacketManager::managePlaceCardAttack(Packet::placeAttackPacket* placeAttackPacket) {
    GameManager* gm = GameManager::getInstance();

    bool adverse = !(placeAttackPacket->data.pseudo == Player::getPlayer()->getName());
    unsigned cardId = placeAttackPacket->data.idCard;
    unsigned cardPosition = placeAttackPacket->data.cardPosition;
    int targetPosition = placeAttackPacket->data.targetPosition;
    unsigned heal = placeAttackPacket->data.heal;

    if(gm->isTurn()) {
        gm->placeCardAndAttack(false, cardId, cardPosition, targetPosition, heal);

        /* Lock, signal other thread and unlock */
        pthread_mutex_lock(&wizardDisplay->packetStackMutex);
        pthread_cond_broadcast(&wizardDisplay->packetStackCond);
        pthread_mutex_unlock(&wizardDisplay->packetStackMutex);

    } else {
        if(adverse) {
            gm->placeAdverseCardAndAttack(false, cardId, cardPosition, targetPosition, heal);
        } else {
            WizardLogger::warning("Cela doit se faire avec les mutex");
        }
    }

}

void PacketManager::manageEndGame(const Packet::endGamePacket* endPacket) {
    // delete GameManager::getInstance();

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
 * Send to the server, the new card that we would like place
 *
 * @param idCard of the new card
 */
void PacketManager::sendPlaceCard(const int idCard) {
    if(GameManager::getInstance()->isTurn()) {
        Packet::intPacket *placePack = new Packet::intPacket();

        WizardLogger::info("Carte à placer " + std::to_string(idCard));

        placePack->ID = Packet::C_PLACE_CARD_ID;
        placePack->data = idCard;

        WizardLogger::info("Carte à placer " + std::to_string(placePack->data));

        conn->sendPacket((Packet::packet*) placePack, sizeof(*placePack));
        delete placePack;
    } else {
        WizardLogger::warning("Impossible de placer une carte, ce n'est pas à votre tour de joueur");
    }
}

/**
 * Send to the server that a card attack an other card
 *
 * @param cardPosition the position of the card which make attack
 * @param targetPosition of the card which IS attacked (-1 for adverse player)
 */
void PacketManager::sendAttack(const unsigned cardPosition, const int targetPosition) {
    if(GameManager::getInstance()->isTurn()) {
        Packet::twoCardPacket *attackPack = new Packet::twoCardPacket();

        attackPack->ID = Packet::C_ATTACK_ID;
        attackPack->cardOne = static_cast<int>(cardPosition);
        attackPack->cardTwo = static_cast<int>(targetPosition);

        WizardLogger::info("Carte: " + std::to_string(static_cast<int>(cardPosition))
                           + " attaque: " + std::to_string(static_cast<int>(targetPosition)));

        conn->sendPacket((Packet::packet*) attackPack, sizeof(*attackPack));
        delete attackPack;
    } else {
        WizardLogger::warning("Impossible d'attaquer, ce n'est pas à votre tour de joueur");
    }
}


/**
 * [Send] Current player place card and attack an other
 *
 * @param idCard the new card
 * @param targetPosition the target card wich will be attack (-1 for adverse player)
 */
void PacketManager::sendPlaceCardAttack(const unsigned idCard, const int targetPosition) {
    if(GameManager::getInstance()->isTurn()) {
        Packet::twoCardPacket *placeAttackPack = new Packet::twoCardPacket();

        placeAttackPack->ID = Packet::C_PLACE_CARD_MAKE_SPELL_ID;
        placeAttackPack->cardOne = idCard;
        placeAttackPack->cardTwo = targetPosition;

        conn->sendPacket((Packet::packet*) placeAttackPack, sizeof(*placeAttackPack));
        delete placeAttackPack;
    } else {
        WizardLogger::warning(
                    "Impossible de placer une carte et attaquer, ce n'est pas à votre tour de joueur");
    }
}


/**
 * Inform server that we have finish our turn
 */
void PacketManager::endTurn() {
    if(GameManager::getInstance()->isTurn()) {
        /* Create and specify a new logoutPacket */
        Packet::packet *endTurn = new Packet::packet();
        endTurn->ID = Packet::END_TURN_ID;

        /* Send it to the server */
        conn->sendPacket((Packet::packet*) endTurn, sizeof(*endTurn));

        /* Clean memory */
        delete endTurn;
    } else {
        WizardLogger::warning("Impossible de finir le tour, ce n'est pas à votre tour de joueur");
    }
}

/**
 * Inform server that we (rage) quit party and we loose
 */
void PacketManager::quit() {
    //     delete GameManager::getInstance();

    /* Create and specify a new logoutPacket */
    Packet::packet *quit = new Packet::packet();
    quit->ID = Packet::QUIT_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet::packet*) quit, sizeof(*quit));
    
    /* Clean memory */
    delete quit;
}

void PacketManager::manageError(Packet::intPacket* errorPacket) {
    WizardLogger::warning("Erreur: " + std::to_string(errorPacket->data));

    /* Lock, signal other thread and unlock */
    pthread_mutex_lock(&wizardDisplay->packetStackMutex);
    wizardDisplay->packetErrorStack.push_back(errorPacket->data);
    pthread_cond_broadcast(&wizardDisplay->packetStackCond);
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);
}
