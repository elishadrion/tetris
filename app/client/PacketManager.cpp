#include "PacketManager.hpp"

extern Connection *conn;

void PacketManager::managePacket(Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {
        /* LOGIN PROCESS */
        case Packet::LOGIN_REQ_ID :       WizardLogger::warning("Paquet invalide reçu : LoginRequest");
                                          break;
        case Packet::REGIST_REQ_ID :      WizardLogger::warning("Paquet invalide reçu : RegistrationRequest");
                                          break;
        case Packet::LOGIN_RES_ID :       loginResult((Packet::loginResultPacket*) customPacket);
                                          break;
        case Packet::DISCONNECT_ID :      WizardLogger::warning("Paquet invalide reçu : DisconnectInfo");
                                          break;
        /* COLLECTIONS/DECKS/CARDS PROCESS */
        case Packet::COLLECTION_REQ_ID :  WizardLogger::warning("Paquet invalide reçu : CollectionRequest");
                                          break;
        case Packet::COLLECTION_LIST_ID : collectionResult((Packet::collectionListPacket*) customPacket);
                                          break;
        default :                         WizardLogger::error("Paquet inconnu reçu : "+customPacket->ID);
                                          break;
    }
}

//======================================================================================

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
    conn->sendPacket((Packet*) loginPacket, sizeof(*loginPacket));
    
    /* Clean memory */
    delete loginPacket;
}

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
    conn->sendPacket((Packet*) registrationPacket, sizeof(*registrationPacket));
    
    /* Clean memory */
    delete registrationPacket;
}

void PacketManager::sendDisconnection() {
    /* Create and specify a new logoutPacket */
    Packet::packet *logoutPacket = new Packet::packet();
    logoutPacket->ID = Packet::DISCONNECT_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet*) logoutPacket, sizeof(*logoutPacket));
    
    /* Clean memory */
    delete logoutPacket;
}

void PacketManager::requestCollection() {
    /* Create and specify a new collectionRequest packet */
    Packet::packet *collReqPacket = new Packet::packet();
    collReqPacket->ID = Packet::COLLECTION_REQ_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet*) collReqPacket, sizeof(*collReqPacket));
    
    /* Clean memory */
    delete collReqPacket;
}

void PacketManager::manageFriend(const char* pseudo, bool remove) {
    Packet::tchatManagPacket* manageFriendPacket = new Packet::tchatManagPacket();
    
    /* Set ID to addFriendRequest or removeFriendRequest */
    if (remove)
        manageFriendPacket->ID = Packet::FRIEND_DEL_ID;
    else
        manageFriendPacket->ID = Packet::FRIEND_ADD_ID;
    
    /* Send pseudo */
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        manageFriendPacket->pseudo[i] = pseudo[i];
    }
    
    /* Send it to the server */
    conn->sendPacket((Packet*) manageFriendPacket, sizeof(*manageFriendPacket));
    
    /* Clean memory */
    delete manageFriendPacket;
}

void PacketManager::askFriendsList() {
    Packet::packet* friendsReqPacket = new Packet::packet();
    
    /* Set ID and send it */
    friendsReqPacket->ID = FRIENDS_REQ_ID;
    conn->sendPacket((Packet*) friendsReqPacket, sizeof(*friendsReqPacket));
    
    /* Clean memory */
    delete friendsReqPacket;
}

//======================================================================================

void PacketManager::loginResult(const Packet::loginResultPacket* resultPacket) {
    /* Check if size is correct to detect corrupted packet */
    if (resultPacket->size != sizeof(int)) {
        WizardLogger::error("Paquet de résulta de login corrompu reçu ("
        +std::to_string(resultPacket->size)+"/"+std::to_string(sizeof(int))+")");
    } else if (resultPacket->resultCode != 0) {
        display->displayLoginResult("Erreur durant le login");
    } else {
        display->valideLogin();
    }
}

void PacketManager::collectionResult(const Packet::collectionListPacket* collectionPacket) {
    /* Check if size is correct to detect corrupted packet */
    if (collectionPacket->size != sizeof(collectionPacket->cartesList)) {
        WizardLogger::error("Paquet de collection corrompu reçu ("
        +std::to_string(collectionPacket->size)+"/"+std::to_string(sizeof(collectionPacket->cartesList))+")");
    } else {
        std::vector<int>* cardList = new std::vector<int>();
        for (int i = 0 ; i < MAX_CARTES ; ++i) {
            if (collectionPacket->cartesList[i] == 1) {
                cardList->push_back(i);
            } else if (collectionPacket->cartesList[i] == 2) {
                cardList->push_back(i);
                cardList->push_back(i);
            }
        }
        //TODO display->updateCollection(cardList->size(), (int*) &cardList[0]); /* Now, vector are contigous */
        delete cardList;
    }
}
