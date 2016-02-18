#include "CommService.hpp"

extern Connection *conn;

void CommService::managePacket(Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {
        case Packet::LOGIN_REQ_ID :       WizardLogger::warn("Paquet invalide reçu : LoginRequest");
                                          break;
        case Packet::DISCONNECT_ID :      WizardLogger::warn("Paquet invalide reçu : DisconnectInfo");
                                          break;
        case Packet::COLLECTION_REQ_ID :  WizardLogger::warn("Paquet invalide reçu : CollectionRequest");
                                          break;
        case Packet::COLLECTION_LIST_ID : //TODO
                                          break;
        default :                         WizardLogger::warn("Paquet inconnu reçu");
                                          break;
    }
}

void CommService::makeLoginRequest(const string pseudo, const string password) {
    Packet::loginRequestPacket *loginPacket = new Packet::loginRequestPacket();
    for (int i = 0 ; i < pseudo.size() ; ++i) {
        loginPacket->pseudo[i] = pseudo.at(i);
    }
    for (int i = 0 ; i < password.size() ; ++i) {
        loginPacket->password[i] = password.at(i);
    }
    
    conn->sendPacket((Packet*) loginPacket, sizeof(char)*60+Packet::packetSize);
}

void CommService::sendDisconnection() {
    
}
