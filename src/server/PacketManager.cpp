#include "PacketManager.hpp"

void PacketManager::manage_packet(Player *player, Packet::packet* customPacket) {
    /* We get ID of the packet after cast void* to packet* */
    switch(customPacket->ID) {

        case Packet::DISCONNECT_ID :      manage_disconnect_request(player, customPacket);
                                          break;

        default :                         std::cout << "Paquet inconnue reçu" << std::endl;
                                          break;
    }
}

//===========================LOGIN PROCESS===========================================

void PacketManager::manage_disconnect_request(Player* player, Packet::packet* disconnectPacket) {
    std::cout << player->get_name() + " se déconnecte" << std::endl;
    player->logout();
}

void PacketManager::sendError(Player* player) {
    Packet::intPacket* errorPacket = new Packet::intPacket();

    errorPacket->ID = Packet::ERROR_ID;
    errorPacket->data = 0;

    /* Send and free */
    player->sendPacket((Packet::packet*) errorPacket, sizeof(*errorPacket));
    delete errorPacket;
}
