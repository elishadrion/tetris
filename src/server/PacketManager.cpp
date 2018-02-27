#include "PacketManager.hpp"

void PacketManager::manage_packet(Player *player, void* packet) {
    /* We get ID of the packet after cast void* to packet* */
    Packet::packet* temp_packet = reinterpret_cast<Packet::packet*>(packet);
    switch(temp_packet->ID) {
        //LOGIN ET SIGNUP
        case Packet::LOGIN_REQ_ID :     manage_login_request(reinterpret_cast<Packet::loginRequestPacket*>(packet));
        								break;
        case Packet::REGIST_REQ_ID:     manage_signup_request(reinterpret_cast<Packet::loginRequestPacket*>(packet));
                                        break;
        case Packet::DISCONNECT_ID:     manage_disconnect_request;
                                        break;
        //JEU
        case Packet::PLAY_REQUEST_ID:   manage_play_request(player);
                                        break;
        case Packet::MOVE_TETRIMINOS:   manage_move_tetriminos_request(player, reinterpret_cast<Packet::intPacket*>(packet));
                                        break;
        default :                       WizardLogger::warning("Paquet inconnue reçu: " +
                                                        std::to_string(temp_packet->ID));
                                        break;
    }
}

//===========================LOGIN & SIGNUP===========================================

Player* PacketManager::manage_login_request(Packet::loginRequestPacket* packet) {
    return PlayerManager::login(std::string(packet->username), std::string(packet->password), packet->sockfd);
}

Player* PacketManager::manage_signup_request(Packet::loginRequestPacket* packet) {
    return PlayerManager::signup(std::string(packet->username), std::string(packet->password), packet->sockfd);
}

void PacketManager::manage_disconnect_request(Player* player) {
    PlayerManager::logout(player);
}


//===========================JEU===========================================


void PacketManager::manage_play_request(Player* player) {
    WizardLogger::info("Reçu une demande de jeu");
    PlayerManager::manage_new_player(player);
}

void PacketManager::manage_move_tetriminos_request(Player* player, Packet::intPacket* packet) {
    exit(0);
    WizardLogger::info(player->get_username()+" a fait le move : "+ std::to_string(packet->data));
    player->get_room()->move_tetriminos(player, packet->data);
}

//===========================ENVOI===========================================

void PacketManager::send_game_waiting(Player* player) {
    WizardLogger::info("Envoi d'un game waiting");

    Packet::packet* packet = new Packet::packet();
    packet->ID = Packet::GAME_WAITING_ID;
    player->send_packet(packet, sizeof(*packet));
    delete packet;
}

void PacketManager::send_game_ready(Player* player) {
    WizardLogger::info("Envoi d'un game ready");
    Packet::intPacket* packet = new Packet::intPacket();
    packet->ID = Packet::GAME_READY_ID;
    packet->data = 1;
    //On doit savoir si le joueur contrôle la grille 1 ou 2
    if ((player->get_room()->get_player(0) == player)) {packet->data = 0;}
    player->send_packet(packet, sizeof(*packet));
    delete packet;
}

void PacketManager::send_error(Player* player) {
    Packet::intPacket* errorPacket = new Packet::intPacket();

    errorPacket->ID = Packet::ERROR_ID;
    errorPacket->data = 0;

    /* Send and free */
    player->send_packet((Packet::packet*) errorPacket, sizeof(*errorPacket));
    delete errorPacket;
}
