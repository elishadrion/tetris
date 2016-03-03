#ifndef PACKET_HPP
#define	PACKET_HPP

#include <string>

#include "common/Constants.hpp"

class Packet {
public:
    /* All packet ID */
    enum IDList {
        /* LOGIN PROCESS */
        LOGIN_REQ_ID = 11,
        REGIST_REQ_ID = 12,
        LOGIN_RES_ID = 13,
        DISCONNECT_ID = 14,
        /* COLLECTIONS/DECKS/CARDS PROCESS */
        COLLECTION_REQ_ID = 21,
        COLLECTION_LIST_ID = 22,
        DECK_REQ_ID = 23,
        DECK_CONT_ID = 24,
        CARTE_REQ_ID = 25,
        CARTE_INFO_ID = 26,
        /* TCHAT & FRIEND PROCESS */
        TCHAT_CONV_REQ_ID = 31,
        TCHAT_NEW_CONV_ID = 32,
        TCHAT_MESSAGE_ID = 33,
        TCHAT_END_REQ_ID = 34,
        TCHAT_END_CONV_ID = 35,
        FRIEND_ADD_ID = 36,
        FRIEND_DEL_ID = 37,
        FRIENDS_REQ_ID = 38,
        FRIENDS_LIST_ID = 39,
        //TODO launch game + game process
    };
    
    /* Default size of all packets (without data) */
    static const int packetSize = sizeof(int)*2;
    
    /* Maximum size of a packets TODO */
    static const int packetMaxSize = sizeof(int[200])+packetSize;
    
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
        int size = sizeof(int)*MAX_CARDS;
        int cartesList[MAX_CARDS];
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
        int size = sizeof(int)+sizeof(char)*MAX_DESCRITION_SIZE;
        int carteID;
        char cartesDescription[MAX_DESCRITION_SIZE]; //TODO description has name ??
    } carteInfosPacket;
    
    /* Tchat new/del (or friend) request */
    typedef struct {
        int ID;
        int size = sizeof(char)*MAX_PSEUDO_SIZE;
        char pseudo[MAX_PSEUDO_SIZE];
    } tchatManagPacket;
    
    /* Tchat message packet (width*height) */
    typedef struct {
        int ID = TCHAT_MESSAGE_ID;
        int size = sizeof(char)*MESSAGES_MAX_SIZE;
        char pseudo[MESSAGES_MAX_SIZE];
    } tchatMessagePacket;
    
    /* friends list (cannot be something else than a vector) */
    typedef struct {
        int ID = FRIENDS_LIST_ID;
        int size;
        char friendsList[MAX_FRIENDS*MAX_PSEUDO_SIZE];
    } friendsListPacket;
};

#endif	/* PACKET_HPP */
