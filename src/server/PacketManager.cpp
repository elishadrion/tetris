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
        case Packet::PLAY_REQUEST_ID:   manage_play_request(player, reinterpret_cast<Packet::playRequestPacket*>(packet));
                                        break;
        case Packet::MOVE_TETRIMINOS:   manage_move_tetriminos_request(player, reinterpret_cast<Packet::intPacket*>(packet));
                                        break;
        case Packet::CHAT_MESSAGE_ID:	receive_chat_message(player, reinterpret_cast<Packet::chatMessagePacket*>(packet));
        								break;
        case Packet::CHAT_MESSAGE_CONN:	receive_chat_connection(player, reinterpret_cast<Packet::pseudoPacket*>(packet));
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

//===========================CHAT==========================================

void PacketManager::receive_chat_connection(Player* player, Packet::pseudoPacket* packet){
    for (auto &i : g_connected){
        if (i->get_username() == player->get_username()){
            //Met l'utilisateur dans le chat (in chat)
            i->set_in_chat_on();
        }
        if (i->is_in_chat()){
            //ENVOIE MSG DE A TT LE MONDE VALIDATION
            WizardLogger::info(i->get_username() +" est dans le chat");
            Packet::chatMessagePacket* packetAllUser = new Packet::chatMessagePacket();
            
            /*std::string user = "server";
            for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
                packetAllUser->sender[i] = user[i];
            }*/
            
            strncpy(packetAllUser->sender,"Server",MAX_PSEUDO_SIZE);
            
            strncpy(packetAllUser->message, "",MAX_MESSAGE_SIZE);
            strcat(packetAllUser->message, i->get_username().c_str());
            strcat(packetAllUser->message, " s'est connecté dans le chat");
            i->send_packet(packetAllUser, sizeof(*packetAllUser));
            delete packetAllUser;
        }
    }
    
}


void PacketManager::receive_chat_message(Player* player, Packet::chatMessagePacket* packet){
    WizardLogger::info(player->get_username() +" envoie un chat");
    WizardLogger::info(packet->message);
    for (auto &i : g_connected){
        if (i->is_in_chat()){
            i->send_packet(packet, sizeof(*packet));
        }
    }
}

//===========================JEU===========================================


void PacketManager::manage_play_request(Player* player,Packet::playRequestPacket* myData) {
    WizardLogger::info("Reçu une demande de jeu de : "+player->get_username());
    PlayerManager::manage_new_player(player,myData->mode);
}

void PacketManager::manage_move_tetriminos_request(Player* player, Packet::intPacket* packet) {
	//On bouge le tetriminos du côté serveur
    player->get_room()->move_tetriminos(player, packet->data);
    //On envoie le move à l'autre joueur
    if(player->get_room()->get_max_size()==2){
        
        if (player->get_room()->get_player(0) == player) {
        	player->get_room()->get_player(1)->send_packet(packet, sizeof(*packet));
        } else {
        	player->get_room()->get_player(0)->send_packet(packet, sizeof(*packet));
        }

    }

}

//===========================ENVOI===========================================

void PacketManager::send_game_waiting(Player* player) {
    WizardLogger::info("Envoi d'un game waiting à : "+player->get_username());

    Packet::packet* packet = new Packet::packet();
    packet->ID = Packet::GAME_WAITING_ID;
    player->send_packet(packet, sizeof(*packet));
    delete packet;
}

void PacketManager::send_game_ready(Player* player, unsigned seed) {
    WizardLogger::info("Envoi d'un game ready à : "+player->get_username());
    Packet::playApprovalPacket* packet = new Packet::playApprovalPacket();
    packet->data = 1;
    packet->seed = seed;
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
