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
    
    /* Logout packet (only optional) */
    typedef struct {
        int ID;
        int size;
        struct data;
    } disconnectPacket;
public:
    /* API for other service */
    int makeLoginRequest(const String, const String);
    int sendDisconnection();
}

/* Create a packet for login request and send it to the server througt socketManager
 * @param pseudo : the user's pseudo to test
 * @param password : the user's password for the user's pseudo
 * @return an error code or 0 if success, you can test these to catch error
 */
int CommService::makeLoginRequest(String pseudo, String password) {
    /* Packet to send to the server ton make a login request :
     * int ID : ID of the packet (for receiver to know how the read data)
     * int size : size of the data struct to see if we have all packet
     * struct data : contains arguments for request. Here, pseudo and password
     */
    loginPacket *loginRequestPacket = new loginPacket();
    loginRequestPacket->ID = LOGIN_REQ_ID;
    loginRequestPacket->size = pseudo.size() + password.size();
    loginRequestPacket->data.pseudo = pseudo;
    loginRequestPacket->data.password = password;
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int) + size
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    return sendToServer((void*) loginRequestPacket, packetSize + loginRequestPacket->size);
}

/* Create a packet for disconnection info and send it to the server througt socketManager
 * @return an error code or 0 if success, you can test these to catch error
 */
int CommService::sendDisconnection() {
    int sizeOfData = 0;

    /* Packet to send to the server ton make a login request :
     * int ID : ID of the packet (for receiver to know how the read data)
     * int size : size of the data struct to see if we have all packet
     * struct data : contains arguments for request. Here, pseudo and password
     */
    disconnectPacket *disconnectInfoPacket = new disconnectPacket();
    disconnectInfoPacket->ID = DISCONNECT_ID;
    disconnectInfoPacket->size = 0;
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int)
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    return sendToServer((void*) disconnectInfoPacket, packetSize);
}


#endif	/* COMMSERVICE_HPP */
