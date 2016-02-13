#ifndef PACKET_HPP
#define	PACKET_HPP

#include <string>
#include <list>

using namespace std;

class Packet {
public:
    /* All packet ID */
    enum IDList {
        LOGIN_REQ_ID = 0,
        DISCONNECT_ID = 1,
        COLLECTION_REQ_ID = 2,
        COLLECTION_LIST_ID = 3,
    };
    
    /* Default size of all packet (without data) */
    const int packetSize = sizeof(int)*2;
    
    /* default packet struct (without data member) */
    typedef struct {
        int ID;
        int size;
    } packet;
    
    /* Login data with 30 as max size for string*/
    typedef struct {
        int ID;
        int size;
        char pseudo[30];
        char password[30];
    } loginPacket;
};

#endif	/* PACKET_HPP */
