#include "PacketManager.hpp"

void PacketManager::manage_packet(Player *player, void* packet) {
    /* We get ID of the packet after cast void* to packet* */
    switch(packet->ID) {
        case Packet::LOGIN_REQ_ID :     manage_login_request(reinterpret_cast<Packet::loginRequestPacket*>(packet);)
        case Packet::DISCONNECT_ID :    manage_disconnect_request(player, packet);
                                        break;

        default :                       WizardLogger::warning("Paquet inconnue reçu");
                                        break;
    }
}

//===========================LOGIN & SIGNUP PROCESS===========================================

Player* PacketManager::manage_login_request(Packet::loginRequestPacket* packet) {
    return PlayerManager::login(std::string(packet->username), std::string(packet->password), packet->sockfd);
}

void PacketManager::manage_signup_request(Packet::loginRequestPacket* packet) {

}

void PacketManager::manage_disconnect_request(Player* player, Packet::packet* disconnectPacket) {
    std::cout << player->get_name() + " se déconnecte" << std::endl;
    player->logout();
}

void PacketManager::sendError(Player* player) {
    Packet::intPacket* errorPacket = new Packet::intPacket();

    errorPacket->ID = Packet::ERROR_ID;
    errorPacket->data = 0;

    /* Send and free */
    player->send_packet((Packet::packet*) errorPacket, sizeof(*errorPacket));
    delete errorPacket;
}
