#include "PacketManager.hpp"

extern Connection *conn;
extern CacheManager *cacheManager;

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
        case Packet::PLAYER_INFO_ID :     playerInfo((Packet::playerInfoPacket*) customPacket);
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

void PacketManager::requestCard(unsigned ID) {
    Packet::carteRequestPacket* cardRequest = new Packet::carteRequestPacket();
    cardRequest->carteID = ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet*) cardRequest, sizeof(*cardRequest));
    
    /* Clean memory */
    delete cardRequest;
}

void PacketManager::registerAsPlayer() {
    Packet::packet* waitGamePacket = new Packet::packet();
    waitGamePacket->ID = Packet::WAITING_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet*) waitGamePacket, sizeof(*waitGamePacket));
    
    /* Clean memory */
    delete waitGamePacket;
}

void PacketManager::cancelWaiting() {
    Packet::packet* cancelWaitingPacket = new Packet::packet();
    cancelWaitingPacket->ID = Packet::CANCEL_ID;
    
    /* Send it to the server */
    conn->sendPacket((Packet*) cancelWaitingPacket, sizeof(*cancelWaitingPacket));
    
    /* Clean memory */
    delete cancelWaitingPacket;
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

void PacketManager::playerInfo(const Packet::playerInfoPacket* playerPacket) {
    WizardLogger::warning(playerPacket->data.pseudo);
    WizardLogger::warning(std::to_string(playerPacket->data.victories));
    WizardLogger::warning(std::to_string(playerPacket->data.defeats));
    display->valideLogin();
}

void PacketManager::getCard(const Packet::cardInfosPacket* cardInfo) {
    Card *newCard = new Card(cardInfo->data.carteID, cardInfo->data.monster, std::string(cardInfo->data.name),
    std::string(cardInfo->data.description), cardInfo->data.energyCost, cardInfo->data.maxHP);
    cacheManager->addToCache(newCard);
}
