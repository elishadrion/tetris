#include <string>
#include <list>

#include "CommService.hpp"

using namespace std;

/* Check ID of the packet to see where to send it
 * @param packet : a void pointer to the struct
 */
void CommService::managePacket(Packet::packet* packet) {
    /* We get ID of the packet */
    switch(packet->ID) {
        case Packet::LOGIN_REQ_ID : //TODO error why client get this ?
                            break;
        case Packet::DISCONNECT_ID : //TODO error why client get this ?
                             break;
        case Packet::COLLECTION_REQ_ID : //TODO error why client get this ?
                                 break;
        case Packet::COLLECTION_LIST_ID : manageCollectionListPacket((Packet::collectionListPacket*) packet);
                                 break;
        default : break;//TODO ERROR
    }
    
}

//=============================================================================================

void CommService::manageCollectionListPacket(Packet::collectionListPacket* collectionListPacket) {
    /* We check data's size for verification */
    if (collectionListPacket->size != sizeof(collectionListPacket->data)) {
        //TODO log corrupted packet
    }
    
    /* We try to get collection and deck list from data (in a try ?) */
    //list collection = collectionListPacket->data.collection;
    //list deck = collectionListPacket->data.deck;
    
    //TODO we set data for user
    //setCollection(collection, deck);
    
    /* We free the memory now */
    delete collectionListPacket;
}

//=============================================================================================

/* Create a packet for login request and send it to the server througt socketManager
 * @param pseudo : the user's pseudo to test
 * @param password : the user's password for the user's pseudo
 */
void CommService::makeLoginRequest(string pseudo, string password) {
    /* Packet to send to the server to make a login request :
     * int ID : ID of the packet (for receiver to know how the read data)
     * int size : size of the data struct to see if we have all packet
     * struct data : contains arguments for request. Here, pseudo and password
     */
    Packet::loginPacket *loginRequestPacket = new Packet::loginPacket();
    loginRequestPacket->ID = Packet::LOGIN_REQ_ID;
    loginRequestPacket->size = sizeof(pseudo)+sizeof(password);
    loginRequestPacket->data.pseudo = pseudo;
    loginRequestPacket->data.password = password;
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int) + size
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    //sendToServer((void*) loginRequestPacket, packetSize + loginRequestPacket->size);
    
    /* We must free the memory now, packet is not needed anymore */
    delete loginRequestPacket;
}

//=============================================================================================

/* Create a packet for disconnection info and send it to the server througt socketManager
 * So server can see a difference between timeout, conneciton crash and volontary disconnection
 */
void CommService::sendDisconnection() {
    int sizeOfData = 0;

    /* Packet to send to the server ton make a login request :
     * int ID : ID of the packet (for receiver to know how the read data)
     * int size : size of the data struct to see if we have all packet
     * struct data : contains arguments for request. Here, pseudo and password
     */
    Packet::packet *disconnectInfoPacket = new Packet::packet();
    disconnectInfoPacket->ID = Packet::DISCONNECT_ID;
    disconnectInfoPacket->size = 0;
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int)
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    //sendToServer((void*) disconnectInfoPacket, packetSize);
    
    /* We must free the memory now, packet is not needed anymore */
    delete disconnectInfoPacket;
}

//=============================================================================================

/* Create a packet to request card and deck collection and send it to the server througt socketManager
 */
void CommService::requestCollection() {
    int sizeOfData = 0;

    /* Packet to send to the server ton make a login request :
     * int ID : ID of the packet (for receiver to know how the read data)
     * int size : size of the data struct to see if we have all packet
     * struct data : contains arguments for request. Here, pseudo and password
     */
    Packet::packet *collecitonRequestPacket = new Packet::packet();
    collecitonRequestPacket->ID = Packet::COLLECTION_REQ_ID;
    collecitonRequestPacket->size = 0;
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int)
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    //sendToServer((void*) collecitonRequestPacket, packetSize);
    
    /* We must free the memory now, packet is not needed anymore */
    delete collecitonRequestPacket;
}
