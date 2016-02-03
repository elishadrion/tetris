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
        LOGIN_REQ = 0;
        DISCONNECT = 1;
        
    }
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
    int sizeOfData = sizeof(pseudo)+sizeof(password);

    /* Packet to send to the server ton make a login request :
     * int ID : ID of the packet (for receiver to know how the read data)
     * int size : size of the data struct to see if we have all packet
     * struct data : contains arguments for request. Here, pseudo and password
     */
    struct loginRequestPacket {
        int ID = LOGIN_REQ;
        int size = sizeOfData;
        struct data {
            pseudo;
            password;
        };
    };
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int) + size
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    return sendToServer((void*) loginRequestPacket, 2*sizeof(int) + sizeOfData);
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
    struct disconnectInfoPacket {
        int ID = DISCONNECT;
        int size = sizeOfData;
        struct data {};
    };
    
    //TODO we inform sendFunction to send a struct of size = 2*sizeof(int) + size
    //PROTOTYPE, wait for Carlos to see how send it (we return succes code ?)
    return sendToServer((void*) disconnectInfoPacket, 2*sizeof(int) + sizeOfData);
}


#endif	/* COMMSERVICE_HPP */
