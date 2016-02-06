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
public:
    /* API for other service */
    void makeLoginRequest(const String, const String);
    void sendDisconnection();
}

/* Create a packet for login request and send it to the server througt socketManager
 * @param pseudo : the user's pseudo to test
 * @param password : the user's password for the user's pseudo
 */
void CommService::makeLoginRequest(String pseudo, String password) {
    /* Packet to send to the server ton make a login request :
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

#endif	/* COMMSERVICE_HPP */
