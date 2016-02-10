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
            //list collection;
            //list deck;
        }; /* We only define data struct, we must include it */
        struct collectionListData data;
    } collectionListPacket;
};

#endif	/* PACKET_HPP */
