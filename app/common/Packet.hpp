#ifndef PACKET_HPP
#define	PACKET_HPP

#include <string>
#include <list>

using namespace std;

//TODO must be implemented somewhere else (global so in main ?)
#define MAX_PSEUDO_SIZE 30
#define MAX_CARTES 200
#define DECK_SIZE 20
#define MAX_CARTE_DESCRITION_SIZE 120

class Packet {
public:
    /* All packet ID */
    enum IDList {
        /* LOGIN PROCESS */
        LOGIN_REQ_ID = 0,
        LOGIN_RES_ID = 1,
        DISCONNECT_ID = 2,
        /* COLLECTIONS/DECKS/CARDS PROCESS */
        COLLECTION_REQ_ID = 3,
        COLLECTION_LIST_ID = 4,
        DECK_REQ_ID = 5,
        DECK_CONT_ID = 6,
        CARTE_REQ_ID = 7,
        CARTE_INFO_ID = 8,
        /* TODO TCHAT PROCESS */
        TCHAT_CONV_REQ_ID = 9,
        TCHAT_NEW_CONV_ID = 10,
        TCHAT_MESSAGE_ID = 11,
        TCHAT_END_REQ_ID = 12,
        TCHAT_END_CONV_ID = 13,
        //TODO launch game + game process
    };
    
    /* Default size of all packets (without data) */
    const int packetSize = sizeof(int)*2;
    
    /* Default packet struct (without data member) */
    typedef struct {
        int ID;
        int size = 0;
    } packet;
    
    /* Login data with 30 as max size for string */
    typedef struct {
        int ID = LOGIN_REQ_ID;
        int size = sizeof(char)*MAX_PSEUDO_SIZE*2;
        char pseudo[MAX_PSEUDO_SIZE];
        char password[MAX_PSEUDO_SIZE];
    } loginRequestPacket;
    
    /* Login result code */
    typedef struct {
        int ID = LOGIN_RES_ID;
        int size = sizeof(int);
        int resultCode;
    } loginResultPacket;
    
    /* Collection list */
    typedef struct {
        int ID = COLLECTION_LIST_ID;
        int size = sizeof(int)*MAX_CARTES;
        int cartesList[MAX_CARTES];
    } collectionListPacket;
    
    /* Deck content request */
    typedef struct {
        int ID = DECK_REQ_ID;
        int size = sizeof(int);
        int deckID;
    } deckRequestPacket;
    
    /* Deck content list */
    typedef struct {
        int ID = DECK_CONT_ID;
        int size = sizeof(int)*DECK_SIZE+sizeof(int);
        int deckID;
        int cartesList[DECK_SIZE];
    } deckContentPacket;
    
    /* Card info request */
    typedef struct {
        int ID = CARTE_REQ_ID;
        int size = sizeof(int);
        int carteID;
    } carteRequestPacket;
    
    /* Card info */
    typedef struct {
        int ID = CARTE_INFO_ID;
        int size = sizeof(int)+sizeof(char)*MAX_CARTE_DESCRITION_SIZE;
        int carteID;
        char cartesDescription[MAX_CARTE_DESCRITION_SIZE]; //TODO description has name ??
    } carteInfosPacket;
};

#endif	/* PACKET_HPP */
