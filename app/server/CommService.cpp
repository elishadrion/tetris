#include "CommService.hpp"

void CommService::managePacket(Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {
        case Packet::LOGIN_REQ_ID :       CommService::manageLoginRequest((Packet::loginRequestPacket*) customPacket);
                                          break;
        case Packet::DISCONNECT_ID :      CommService::manageDisconnectRequest(customPacket);
                                          break;
        case Packet::COLLECTION_REQ_ID :  //TODO
                                          break;
        case Packet::COLLECTION_LIST_ID : WizardLogger::warn("Paquet invalide reçu : CollectionList");
                                          break;
        default :                         WizardLogger::warn("Paquet inconnue reçu");
                                          break;
    }
}

void CommService::manageDisconnectRequest(Packet::packet* disconnectReqPacket) {
    
}

void CommService::manageLoginRequest(Packet::loginRequestPacket* loginReqPacket) {
    if (loginReqPacket->size != sizeof(loginReqPacket->pseudo)+sizeof(loginReqPacket->password)) {
        WizardLogger::error("Paquet de login corrompu reçu");
        return;
    }
    
    std::string pseudo = "";
    int i = 0;
    char ch;
    while((ch = loginReqPacket->pseudo[i]) != NULL && ch != ' ') {
        pseudo += ch;
        ++i;
    }
    std::string password = "";
    i = 0;
    while((ch = loginReqPacket->password[i]) != NULL && ch != ' ') {
        password += ch;
        ++i;
    }
    
    //TODO
    WizardLogger::warn("TEST PSEUDO : "+pseudo);
    WizardLogger::warn("TEST PASSWORD : "+password);
}
