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
        LOGIN_RES_ID = 13, /* Error code to convert in message (popup) */
        DISCONNECT_ID = 14,
        PLAYER_INFO_ID = 15, /* Success so get all player infos needed */
        /* CARDS PROCESS */
        CARTE_REQ_ID = 21,
        CARTE_INFO_ID = 22,
        /* TCHAT & FRIEND PROCESS */
        TCHAT_CONV_REQ_ID = 31, /* Get TCHAT_END_CONV_ID if failed */
        TCHAT_NEW_CONV_ID = 32,
        TCHAT_MESSAGE_ID = 33, /* No success verification */
        TCHAT_END_REQ_ID = 34,
        TCHAT_END_CONV_ID = 35,
        FRIEND_ADD_ID = 36, /* Get FRIEND_DEL_ID if failed */
        FRIEND_DEL_ID = 37,
        FRIENDS_REQ_ID = 38, /* Do you want to be friend ? */
        //TODO launch game + game process
    };
    
    /* Default size of all packets (without data) */
    static const int packetSize = sizeof(int)*2;
    
    /* Default packet struct (without data member) */
    typedef struct {
        int ID;
        int size = 0;
    } packet;

//=========================LOGIN PROCESS=====================================

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
    
    /* Player info */
    typedef struct {
        int ID = PLAYER_INFO_ID;
        struct data {
            char pseudo[MAX_PSEUDO_SIZE];
            unsigned collection[MAX_CARDS];
            int decks[MAX_DECKS];
            char friendsList[MAX_FRIENDS*MAX_PSEUDO_SIZE]; /* Every MAX_PSEUDO_SIZE it's a pseudo */
            unsigned victories;
            unsigned defeats;
        };
        struct data; /* We define it but we must include it */
        int size = sizeof(data);
    } playerInfoPacket;

//========================CARDS PROCESS=======================================
    
    /* Card info request */
    typedef struct {
        int ID = CARTE_REQ_ID;
        int size = sizeof(int);
        int carteID;
    } carteRequestPacket;
    
    /* Card info */
    typedef struct {
        int ID = CARTE_INFO_ID;
        struct data {
            int carteID;
            bool monster;
            char name[MAX_PSEUDO_SIZE];
            char description[MAX_DESCRITION_SIZE];
            unsigned energyCost;
            unsigned maxHP;
        };
        struct data; /* We define it but we must include it */
        int size = sizeof(data);
    } carteInfosPacket;

//====================TCHAT & FRIEND PROCESS================================
    
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

//==========================================================================

//==========================================================================
    
    /* Maximum size of a packets */
    static const int packetMaxSize = sizeof(playerInfoPacket);
};

#endif	/* PACKET_HPP */
