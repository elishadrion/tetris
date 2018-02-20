#include "PacketManager.hpp"

extern Connection *conn;
extern CacheManager *cacheManager;

void PacketManager::manage_packet(void* packet) {
    /* We get ID of the packet after cast void* to packet* */
	Packet::packet* temp_packet = reinterpret_cast<Packet::packet*>(packet);
    switch(temp_packet->ID) {

        /* Login process */
        case Packet::LOGIN_REQ_ID :       WizardLogger::warning("Paquet de requête de login reçu");
                                          break;
        case Packet::REGIST_REQ_ID :      WizardLogger::warning("Paquet de requête d'inscription reçu");
                                          break;
        case Packet::LOGIN_COMPLETE_ID :  login_complete(temp_packet);
                                          break;

        case Packet::DISCONNECT_ID :      WizardLogger::warning("Paquet de déconnection reçu");
                                          break;
        default :                         WizardLogger::warning("Paquet inconnue reçu: " +
                                                            std::to_string(temp_packet->ID));
                                          break;
    }
}


//===========================LOGIN PROCESS===========================================


void PacketManager::login_complete(const Packet::packet* packet) {
    pthread_mutex_lock(&display->packetStackMutex);
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
    
    /* Send it to the server */
    conn->send_packet(loginPacket, sizeof(*loginPacket));
    
    /* Clean memory */
    delete loginPacket;
}

/**
 * Send a login request to the server
 *
 * @param pseudo : pseudo array of the user
 * @param password : password array of the user
 */
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
    
    /* Send it to the server */
    conn->send_packet(registrationPacket, sizeof(*registrationPacket));
    
    /* Clean memory */
    delete registrationPacket;
}

/**
 * Send a disconnection signal to the server (help detect crash)
 */
void PacketManager::send_disconnect_request() {
    /* Create and specify a new logoutPacket */
    Packet::packet *logoutPacket = new Packet::packet();
    logoutPacket->ID = Packet::DISCONNECT_ID;
    
    /* Send it to the server */
    conn->send_packet((Packet::packet*) logoutPacket, sizeof(*logoutPacket));
    
    /* Clean memory */
    delete logoutPacket;
}

