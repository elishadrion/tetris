#include "PacketManager.hpp"



void PacketManager::manage_packet(void* packet) {
    /* We get ID of the packet after cast void* to packet* */
	Packet::packet* temp_packet = reinterpret_cast<Packet::packet*>(packet);
    switch(temp_packet->ID) {

        /* Login process */
        case Packet::LOGIN_REQ_ID :         WizardLogger::warning("Paquet de requête de login reçu");
                                            break;
        case Packet::REGIST_REQ_ID :        WizardLogger::warning("Paquet de requête d'inscription reçu");
                                            break;
        case Packet::LOGIN_ERROR_ID :       login_error();
                                            break;
        case Packet::LOGIN_COMPLETE_ID :    login_complete();
                                            break;
        case Packet::GAME_WAITING_ID:       game_waiting();
                                            break;
        case Packet::GAME_READY_ID:         game_ready(reinterpret_cast<Packet::playApprovalPacket*>(packet));
                                            break;
        case Packet::MOVE_TETRIMINOS:       manage_move_tetriminos_request(reinterpret_cast<Packet::intPacket*>(packet));
                                            break;
        case Packet::CHAT_MESSAGE_ID:       receive_chat_message(reinterpret_cast<Packet::chatMessagePacket*>(packet));
                                            break;
        case Packet::CHAT_USERS_ID:         receive_users_name(reinterpret_cast<Packet::usersInChatPacket*>(packet));
                                            break;
        case Packet::DISCONNECT_ID :        WizardLogger::warning("Paquet de déconnection reçu");
                                            break;
				case Packet::USERS_ID :     receive_users_list(reinterpret_cast<Packet::usersPacket*>(packet));
                                            break;
        default :                           WizardLogger::warning("Paquet inconnue reçu: " +
                                                        std::to_string(temp_packet->ID));
                                            break;
    }
}

//=============================RECEPTION=====================================
//===========================LOGIN & SIGNUP===========================================

void PacketManager::login_complete() {
    pthread_mutex_lock(&display->packetStackMutex);
    pthread_cond_broadcast(&display->packetStackCond);
    pthread_mutex_unlock(&display->packetStackMutex);
}

void PacketManager::login_error() {
    /* Lock, signal other thread and unlock */
    pthread_mutex_lock(&display->packetStackMutex);
    display->packetStack.push_back(reinterpret_cast<void*>(new std::string("Erreur durant le login")));
    pthread_cond_broadcast(&display->packetStackCond);
    pthread_mutex_unlock(&display->packetStackMutex);
}

void PacketManager::send_login_request(const char *pseudo, const char *password) {
    /* Create and complete a new loginPacket */
    Packet::loginRequestPacket *loginPacket = new Packet::loginRequestPacket();
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        loginPacket->username[i] = pseudo[i];
    }
    for (int i = 0 ; i < HASH_SIZE ; ++i) {
        loginPacket->password[i] = password[i];
    }

    conn->send_packet(loginPacket, sizeof(*loginPacket));
    delete loginPacket;
}

void PacketManager::send_signup_request(const char *pseudo, const char *password) {
    /* Create and complete a new loginPacket and modify ID to match registration request */
    Packet::loginRequestPacket *registrationPacket = new Packet::loginRequestPacket();
    registrationPacket->ID = Packet::REGIST_REQ_ID;
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        registrationPacket->username[i] = pseudo[i];
    }
    for (int i = 0 ; i < HASH_SIZE ; ++i) {
        registrationPacket->password[i] = password[i];
    }
		WizardLogger::warning(std::string(reinterpret_cast<char*>(registrationPacket->username))+"Password - "+std::string(reinterpret_cast<char*>(registrationPacket->password)));

    conn->send_packet(registrationPacket, sizeof(*registrationPacket));
    delete registrationPacket;
}

//=============================ENVOI=====================================
//===========================GAME PROCESS===========================================


void PacketManager::send_play_request(int mode) {
    Packet::playRequestPacket* play_request_packet = new Packet::playRequestPacket();
    play_request_packet->mode = mode;
    play_request_packet->socket = conn->get_socket();
    conn->send_packet(play_request_packet, sizeof(*play_request_packet));
    delete play_request_packet;send_friend_request;
}

void PacketManager::game_waiting() {
    WizardLogger::info("Reçu un game waiting du serveur");
    pthread_mutex_lock(&display->packetStackMutex);
    pthread_cond_broadcast(&display->packetStackCond);
    pthread_mutex_unlock(&display->packetStackMutex);
}

void PacketManager::game_ready(Packet::playApprovalPacket* packet) {
    WizardLogger::info("Reçu un game ready du serveur");
    display->packetStack.push_back(reinterpret_cast<void*>(packet->data));
    display->packetStack.push_back(reinterpret_cast<void*>(packet->seed));
    pthread_mutex_lock(&display->packetStackMutex);
    pthread_cond_broadcast(&display->packetStackCond);
    pthread_mutex_unlock(&display->packetStackMutex);

}

void PacketManager::manage_move_tetriminos_request(Packet::intPacket* packet) {
    game_manager->get_game()->move_tetriminos_second_grid(packet->data);
}

/** =================================CHAT============================================
 */

void PacketManager::send_chat_conn(const char *user) {
    Packet::pseudoPacket* chat_request_conn = new Packet::pseudoPacket();
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        chat_request_conn->pseudo[i] = user[i];
    }
    chat_request_conn->ID = Packet::CHAT_MESSAGE_CONN;
    conn->send_packet(chat_request_conn, sizeof(*chat_request_conn));
    delete chat_request_conn;
}


void PacketManager::receive_chat_message(Packet::chatMessagePacket* packet) {
    WizardLogger::info("Paquet de chat reçu");
    salon_chat->chatReceiver(packet->message,packet->sender);

}

void PacketManager::send_chat_message(const char *user, const char *msg){
    Packet::chatMessagePacket* chat_send_msg_to_server = new Packet::chatMessagePacket();
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        chat_send_msg_to_server->sender[i] = user[i];
    }
    for (int i = 0 ; i < MAX_MESSAGE_SIZE ; ++i) {
        chat_send_msg_to_server->message[i] = msg[i];
    }
    chat_send_msg_to_server->ID = Packet::CHAT_MESSAGE_ID;
    conn->send_packet(chat_send_msg_to_server, sizeof(*chat_send_msg_to_server));
    delete chat_send_msg_to_server;
}


void PacketManager::send_friend_request(int action_type, const char *friend_name){

		Packet::friendRequestPacket* friend_Request_Packet = new Packet::friendRequestPacket();
		WizardLogger::info("action type :"+std::to_string(action_type));


		if(action_type==0){
			friend_Request_Packet->action = action_type;
	    friend_Request_Packet->ID = Packet::FRIENDS_ID;

		}
		else if(action_type==1){
			for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
	        friend_Request_Packet->friendName[i] = friend_name[i];
	    }
			friend_Request_Packet->action = action_type;
	    friend_Request_Packet->ID = Packet::FRIENDS_ID;

		}
		else if(action_type==2){

			for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
	        friend_Request_Packet->friendName[i] = friend_name[i];
	    }
			friend_Request_Packet->action = action_type;
	    friend_Request_Packet->ID = Packet::FRIENDS_ID;

		}
		else if(action_type==3){
			friend_Request_Packet->action = action_type;
	    friend_Request_Packet->ID = Packet::FRIENDS_ID;

		}
		else if(action_type==4){
			friend_Request_Packet->action = action_type;
	    friend_Request_Packet->ID = Packet::FRIENDS_ID;
		}
		else if(action_type==5){

			for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
	        friend_Request_Packet->friendName[i] = friend_name[i];
	    }
			friend_Request_Packet->action = action_type;
	    friend_Request_Packet->ID = Packet::FRIENDS_ID;

		}

    conn->send_packet(friend_Request_Packet, sizeof(*friend_Request_Packet));
    delete friend_Request_Packet;
}






void PacketManager::send_stat_request(int action_type){

		Packet::statisticRequestPacket* statistic_request_packet = new Packet::statisticRequestPacket();
		WizardLogger::info("stat action type  :"+std::to_string(action_type));


		statistic_request_packet->action = action_type;
    statistic_request_packet->ID = Packet::STATISTIC_ID;


    conn->send_packet(statistic_request_packet, sizeof(*statistic_request_packet));
    delete statistic_request_packet;
}



void PacketManager::receive_users_name(Packet::usersInChatPacket* packet){
    salon_chat->print_online_users_chat(packet->users_char);
}

void PacketManager::receive_users_list(Packet::usersPacket* packet){
	WizardLogger::info("received Users List");

	WizardLogger::info(packet->users_list);

	friends_manager->printAllUsers(packet->users_list);
}


void PacketManager::send_logout_chat(){
    Packet::packet* send_logout_packet = new Packet::packet();
    send_logout_packet->ID = Packet::CHAT_LOGOUT;
    conn->send_packet(send_logout_packet, sizeof(*send_logout_packet));
}

/**
 * Send a disconnection signal to the server (help detect crash)
 */
void PacketManager::send_disconnect_request() {
    /* Create and specify a new logoutPacket */
    Packet::packet *logoutPacket = new Packet::packet();
    logoutPacket->ID = Packet::DISCONNECT_ID;
    conn->send_packet((Packet::packet*) logoutPacket, sizeof(*logoutPacket));
    delete logoutPacket;
}

void PacketManager::send_move_tetriminos(int _data) {
    Packet::intPacket* packet = new Packet::intPacket();
    packet->ID = Packet::MOVE_TETRIMINOS;
    packet->data = _data;
    //On vérifie bien que le jeu n'est pas fini
    conn->send_packet(packet, sizeof(*packet));
    delete packet;
}
