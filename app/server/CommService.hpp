/* 
 * File:   CommService.hpp
 * Author: Tutul
 *
 * Created on 3 février 2016, 17:55
 */

#ifndef COMMSERVICE_HPP
#define	COMMSERVICE_HPP

class CommService {
    
    /* All packet ID */
    enum IDList {
        LOGIN_REQ_ID = 0,
        DISCONNECT_ID = 1,
    };
    
    /* Default size of all packet (without data) */
    const int packetSize = sizeof(int)*2;
    
    /* default packet struct (can be use for empty data) */
    typedef struct {
        int ID;
        int size;
        struct data;
    } packet;
    
    /* Login packet */
    typedef struct {
        int ID;
        int size;
        struct loginData {
            string pseudo;
            string password;
        }; /* We only define data struct, we must include it */
        struct loginData data;
    } loginPacket;
    
    void manageLoginRequest(loginPacket*)
    void manageDisconnectRequest(packet*)
public:
    /* API for other service */
    void managePacket(void*);
}

void managePacket(void* packet) {
    /* We get ID of the packet */
    switch((packet*) packet->ID) {
        case LOGIN_REQ_ID :     manageLoginRequest((loginPacket*) packet);
                                break;
        case DISCONNECT_ID :    manageDisconnectRequest((packet*) packet);
                                break;
        default :               break;//TODO ERROR
    }
    
}

void manageLoginRequest(loginPacket* loginRequestPacket) {
    /* We check data's size for verification */
    if (loginRequestPacket->size != sizeof(loginRequestPacket->data)) {
        //TODO log corrupted packet
    }
    
    /* We try to get pseudo and password from data (in a try ?) */
    String pseudo = loginRequestPacket->data.pseudo;
    String password = loginRequestPacket->data.password;
    
    //TODO we call the login manager to check pseudo and password
    checkLogin(pseudo, password);
    
    /* We free the memory now */
    delete loginRequestPacket;
}

void manageDisconnectRequest(packet* disconnectInfoPacket) {
    //TODO we call the login manager to check pseudo and password
    registreLogout();
    
    /* We free the memory now */
    delete disconnectInfoPacket;
}


#endif	/* COMMSERVICE_HPP */
