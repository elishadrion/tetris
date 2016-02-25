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
        case Packet::COLLECTION_LIST_ID : //TODO
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
