#include "CommService.hpp"

void CommService::managePacket(Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {
        case Packet::LOGIN_REQ_ID :       CommService::manageDisconnectRequest(customPacket);
                                          break;
        case Packet::DISCONNECT_ID :      CommService::manageLoginRequest((Packet::loginPacket*) customPacket);
                                          break;
        case Packet::COLLECTION_REQ_ID :  //TODO
                                          break;
        case Packet::COLLECTION_LIST_ID : logger->warn("Paquet invalide reçu : CollectionList");
                                          break;
        default :                         logger->warn("Paquet inconnue reçu");
                                          break;
    }
}

void CommService::manageDisconnectRequest(Packet::packet* disconnectReqPacket) {
    
}

void CommService::manageLoginRequest(Packet::loginPacket* loginReqPacket) {
    
}
