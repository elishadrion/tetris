#include <string>
#include <list>

using namespace std;

/* Check ID of the packet to see where to send it
 * @param packet : a void pointer to the struct
 */
void CommService::managePacket(void* packet) {
    /* We get ID of the packet */
    switch((packet*) packet->ID) {
        case LOGIN_REQ_ID : //TODO error why client get this ?
                            break;
        case DISCONNECT_ID : //TODO error why client get this ?
                             break;
        case COLLECTION_REQ_ID : //TODO error why client get this ?
                                 break;
        case COLLECTION_LIST_ID : manageCollectionListPacket((collectionListPacket*) packet);
                                 break;
        default : break;//TODO ERROR
    }
    
}

//=============================================================================================

void CommService::manageCollectionListPacket(collectionListPacket* collectionListPacket) {
    /* We check data's size for verification */
    if (collectionListPacket->size != sizeof(collectionListPacket->data)) {
        //TODO log corrupted packet
    }
    
    /* We try to get collection and deck list from data (in a try ?) */
    list collection = collectionListPacket->data.collection;
    list deck = collectionListPacket->data.deck;
    
    //TODO we set data for user
    setCollection(collection, deck);
    
    /* We free the memory now */
    delete collectionListPacket;
}

//=============================================================================================

/* Create a packet for login request and send it to the server througt socketManager
 * @param pseudo : the user's pseudo to test
 * @param password : the user's password for the user's pseudo
 */
void CommService::makeLoginRequest(String pseudo, String password) {
    /* Packet to send to the server to make a login request :
     * int ID : ID of the packet (for receiver to know how the read data)
     * int size : size of the data struct to see if we have all packet
     * struct data : contains arguments for request. Here, pseudo and password
     */
    loginPacket *loginRequestPacket = new loginPacket();
    loginRequestPacket->ID = LOGIN_REQ_ID;
    loginRequestPacket->size = sizeof(pseudo)+sizeof(password);
    loginRequestPacket->data.pseudo = pseudo;
    loginRequestPacket->data.password = password;
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int) + size
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    sendToServer((void*) loginRequestPacket, packetSize + loginRequestPacket->size);
    
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
    packet *disconnectInfoPacket = new packet();
    packet->ID = DISCONNECT_ID;
    packet->size = 0;
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int)
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    sendToServer((void*) disconnectInfoPacket, packetSize);
    
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
    packet *collecitonRequestPacket = new packet();
    packet->ID = COLLECTION_REQ_ID;
    packet->size = 0;
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int)
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    sendToServer((void*) collecitonRequestPacket, packetSize);
    
    /* We must free the memory now, packet is not needed anymore */
    delete collecitonRequestPacket;
}

#endif	/* COMMSERVICE_HPP */
