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
        DISCONNECT_ID = 14, /* DEFAULT PACKET */
        PLAYER_INFO_ID = 15, /* Success so get all player infos needed */
        /* CARDS PROCESS */
        CARTE_REQ_ID = 21,
        CARTE_INFO_ID = 22,
        CARTE_IMG_ID = 23,
        /* TCHAT & FRIEND PROCESS */
        TCHAT_CONV_REQ_ID = 31, /* Get TCHAT_END_CONV_ID if failed */
        TCHAT_NEW_CONV_ID = 32,
        TCHAT_MESSAGE_ID = 33, /* No success verification */
        TCHAT_END_REQ_ID = 34,
        TCHAT_END_CONV_ID = 35,
        FRIEND_ADD_ID = 36, /* Get FRIEND_DEL_ID if failed (use managPacket) */
        FRIEND_DEL_ID = 37,  /* !> use managPacket */
        FRIENDS_REQ_ID = 38, /* Do you want to be friend ? (use managPacket) */
        FRIENDS_LIST_ID = 39,
        /* LAUNCHING GAME PROCESS */
        WAITING_ID = 41, /* DEFAULT PACKET */
        CANCEL_ID = 42, /* DEFAULT PACKET */
        LAUNCH_ID = 43, /* DEFAULT PACKET - ask for deck */
        DECK_CHOOS_ID = 44, /* !> use login error packet for int */
        /* GAME PROCESS */
        TURN_ID = 51, /* Signal the current player turn (use managPacket) */
        DRAW_ID = 52, /* !> use managePacket */
        ASK_DROP_ID = 53, /* Ask to draw a certain amount of card */
        DROP_ID = 54, /* A packet by droped card (use loginError) */
        ATTACK_ID = 55,
        SPELL_ID = 56,
        END_TURN_ID = 57, /* Send to server to signal end of turn (DEFAULT PACKET) */
        QUIT_ID = 58, /* DEFAULT PACKET */
        END_GAME_ID = 59, /* !> use actionPacket */
    };
    
    /* Default size of all packets (without data) */
    static const int packetSize = sizeof(int)*2;
    
    /* Default packet struct (without data member) */
    typedef struct {
        int ID;
        int size = 0;
    } packet;

//=========================LOGIN PROCESS=================================

    /* Login or register packet */
    typedef struct {
        int ID = LOGIN_REQ_ID;
        int size = sizeof(char)*MAX_PSEUDO_SIZE*2;
        char pseudo[MAX_PSEUDO_SIZE];
        char password[MAX_PSEUDO_SIZE];
    } loginRequestPacket;
    
    /* Login error code */
    typedef struct {
        int ID = LOGIN_RES_ID;
        int size = sizeof(int);
        int resultCode;
    } loginResultPacket;
    
    /* Player info (sucess login) */
    typedef struct {
        int ID = PLAYER_INFO_ID;
        typedef struct {
            char pseudo[MAX_PSEUDO_SIZE];
            unsigned collection[MAX_CARDS];
            int decks[MAX_DECKS];
            char friendsList[MAX_FRIENDS*MAX_PSEUDO_SIZE]; /* Every MAX_PSEUDO_SIZE it's a pseudo */
            unsigned victories;
            unsigned defeats;
        } playerData;
        int size = sizeof(playerData);
        playerData data; /* We define it but we must include it */
    } playerInfoPacket;

//========================CARDS PROCESS===================================
    
    /* Card info request */
    typedef struct {
        int ID = CARTE_REQ_ID;
        int size = sizeof(int);
        unsigned carteID;
    } carteRequestPacket;
    
    /* Card info */
    typedef struct {
        int ID = CARTE_INFO_ID;
        typedef struct {
            unsigned carteID;
            bool monster;
            char name[MAX_PSEUDO_SIZE];
            char description[MAX_DESCRITION_SIZE];
            unsigned energyCost;
            unsigned maxHP;
        } cardData;
        int size = sizeof(cardData);
        cardData data; /* We define it but we must include it */
    } cardInfosPacket;
    
    typedef struct {
        int ID = CARTE_IMG_ID;
        int size = 80000; /* Max size is currently 80Ko */
        void* data[80000]; /* Must be complete image binary data */
    } cardImgPacket;

//====================TCHAT & FRIEND PROCESS==============================
    
    /* Tchat new/del (or friend or new game or turn) request */
    typedef struct {
        int ID;
        int size = sizeof(char)*MAX_PSEUDO_SIZE;
        char pseudo[MAX_PSEUDO_SIZE];
    } managPacket;
    
    /* Tchat message packet (width*height) */
    typedef struct {
        int ID = TCHAT_MESSAGE_ID;
        int size = sizeof(char)*MESSAGES_MAX_SIZE;
        char pseudo[MESSAGES_MAX_SIZE];
    } tchatMessagePacket;
    
    /* Player's friends list only */
    typedef struct {
        int ID = FRIENDS_LIST_ID;
        int size = sizeof(char)*MAX_FRIENDS*MAX_PSEUDO_SIZE;
        char friendsList[MAX_FRIENDS*MAX_PSEUDO_SIZE]; /* Every MAX_PSEUDO_SIZE it's a pseudo */
    } friendListPacket;

//=========================GAME=============================================
    
    /* Packet for attack or play spell (or win game) */
    typedef struct {
        int ID;
        typedef struct {
            char pseudo[MESSAGES_MAX_SIZE]; /* Player doing attack or spell or winning */
            int target; /* Target card ID (-1 for player) OR ID for spell card to play (or win card) */
        } actionData;
        int size = sizeof(actionData);
        actionData data;
    } actionPacket;

//==========================================================================
    
    /* Maximum size of a packets */
    static const int packetMaxSize = sizeof(cardImgPacket);
};

#endif	/* PACKET_HPP */
