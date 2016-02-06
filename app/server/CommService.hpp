/* 
 * File:   CommService.hpp
 * Author: Tutul
 *
 * Created on 3 février 2016, 17:55
 */

#ifndef COMMSERVICE_HPP
#define	COMMSERVICE_HPP

#include <string>
#include <list>

using namespace std;

class CommService {
    
    /* All packet ID */
    enum IDList {
        LOGIN_REQ_ID = 0,
        DISCONNECT_ID = 1,
        COLLECTION_REQ_ID = 2,
        COLLECTION_LIST_ID = 3,
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
    
    /* Collection list packet */
    typedef struct {
        int ID;
        int size;
        struct collectionListData {
            list collection;
            list deck;
        }; /* We only define data struct, we must include it */
        struct collectionListData data;
    } collectionListPacket;
    
    void manageLoginRequest(loginPacket*);
    void manageDisconnectRequest(packet*);
    void manageCollectionRequest(collectionListPacket*);
public:
    /* API for other service */
    void managePacket(void*);
    void sendCollectionList(list, list);
};

//=============================================================================================

/* Check ID of the packet to see where to send it
 * @param packet : a void pointer to the struct
 */
void managePacket(void* packet) {
    /* We get ID of the packet */
    switch((packet*) packet->ID) {
        case LOGIN_REQ_ID :     manageLoginRequest((loginPacket*) packet);
                                break;
        case DISCONNECT_ID :    manageDisconnectRequest((packet*) packet);
                                break;
        case COLLECTION_REQ_ID : manageCollectionRequest((packet*) packet);
                                 break;
        case COLLECTION_LIST_ID : //TODO error why server get this ?
                                 break;
        default : break;//TODO ERROR
    }
    
}

//=============================================================================================

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

//=============================================================================================

void manageDisconnectRequest(packet* disconnectInfoPacket) {
    //TODO we call the login manager to check pseudo and password
    registreLogout();
    
    /* We free the memory now */
    delete disconnectInfoPacket;
}

//=============================================================================================

void manageCollectionRequest(packet* collectionRequestPacket) {
    //TODO get collection list (card and deck)
    getCollection();
    
    /* We free the memory now */
    delete loginRequestPacket;
}

//=============================================================================================

/* Create a packet with palyer's card/deck and send it to the server througt socketManager
 * @param collection : the user's card's list
 * @param deck : the user's deck list
 */
void CommService::sendCollectionList(list collection, list deck) {
    /* Packet to send to the server to make a login request :
     * int ID : ID of the packet (for receiver to know how the read data)
     * int size : size of the data struct to see if we have all packet
     * struct data : contains arguments for request. Here, pseudo and password
     */
    collectionListPacket *collectionListPacket = new collectionListPacket();
    collectionListPacket->ID = COLLECTION_LIST_ID;
    collectionListPacket->size = sizeof(collection)+sizeof(deck);
    collectionListPacket->data.collection = collection;
    collectionListPacket->data.deck = deck;
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int) + size
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    sendToServer((void*) collectionListPacket, packetSize + collectionListPacket->size);
    
    /* We must free the memory now, packet is not needed anymore */
    delete collectionListPacket;
}

#endif	/* COMMSERVICE_HPP */
