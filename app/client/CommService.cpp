#include "CommService.hpp"

void CommService::managePacket(Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {
        case Packet::LOGIN_REQ_ID :       logger->warn("Paquet invalide reçu : LoginRequest");
                                          break;
        case Packet::DISCONNECT_ID :      logger->warn("Paquet invalide reçu : DisconnectInfo");
                                          break;
        case Packet::COLLECTION_REQ_ID :  logger->warn("Paquet invalide reçu : CollectionRequest");
                                          break;
        case Packet::COLLECTION_LIST_ID : //TODO
                                          break;
        default :                         logger->warn("Paquet inconnue reçu");
                                          break;
    }
}

void makeLoginRequest(const string pseudo, const string password) {
    
}

void sendDisconnection() {
    
}
