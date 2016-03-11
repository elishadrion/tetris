#ifndef PACKET_HPP
#define	PACKET_HPP

#include <string>

#include "common/Constants.hpp"

class Packet {
public:
    /* All packet ID */
    enum IDList {
        /* LOGIN PROCESS (all but the last in a mini-feature) */
        LOGIN_REQ_ID = 11, /* DEFAULT PACKET */
        REGIST_REQ_ID = 12, /* DEFAULT PACKET */
        LOGIN_RES_ID = 13, /* Error code to convert in message (intPacket) */
        PLAYER_INFO_ID = 14, /* Success so get all player infos needed */
        DISCONNECT_ID = 15, /* DEFAULT PACKET */
        /* CARDS PROCESS */
        CARTE_REQ_ID = 21, /* intPacket */
        CARTE_INFO_ID = 22, /* Send all card info (no img) */
        CARTE_IMG_REQ_ID = 23, /* intPacket */
        CARTE_IMG_ID = 24, /* intPacket */
        /* TCHAT */
        TCHAT_CONV_REQ_ID = 31, /* Get TCHAT_END_CONV_ID if failed (pseudoPacket) */
        TCHAT_NEW_CONV_ID = 32, /* pseudoPacket */
        TCHAT_MESSAGE_ID = 33, /* No success verification */
        TCHAT_END_REQ_ID = 34, /* pseudoPacket */
        TCHAT_END_CONV_ID = 35, /* pseudoPacket */
        /* FRIEND */
        FRIEND_ADD_ID = 41, /* Get FRIEND_DEL_ID if failed (use pseudoPacket) */
        FRIEND_DEL_ID = 42,  /* pseudoPacket */
        FRIENDS_REQ_ID = 43, /* Do you want to be friend ? (use pseudoPacket) */
        FRIENDS_LIST_REQ_ID = 44, /* DEFAULT PACKET */
        FRIENDS_LIST_ID = 45, /* Send all friendList */
        /* LAUNCHING GAME PROCESS */
        WAITING_ID = 51, /* DEFAULT PACKET */
        CANCEL_ID = 52, /* DEFAULT PACKET */
        LAUNCH_ID = 53, /* DEFAULT PACKET - ask for deck */
        DECK_CHOOS_ID = 54, /* intPacket */
        /* GAME PROCESS */
        TURN_ID = 61, /* Signal the current player turn */
        DRAW_ID = 62, /* intPacket */
        ASK_DROP_ID = 63, /* Ask to draw a certain amount of card */
        DROP_ID = 64, /* A packet by droped card (use intPacket) */
        ATTACK_ID = 65, /* send attacker, target's ID (-1 for player) */
        SPELL_ID = 66, /* send wizard, speel's ID */
        END_TURN_ID = 67, /* Send to server to signal end of turn (DEFAULT PACKET) */
        QUIT_ID = 68, /* DEFAULT PACKET */
        END_GAME_ID = 69, /* !> use actionPacket */
    };
    
    /* Default size of all packets (without data) */
    static const int packetSize = sizeof(int)*2;
    
    /* Default packet struct (without data member) */
    typedef struct {
        int ID;
        int size = 0;
    } packet;
    
    /* Packet with only int */
    typedef struct {
        int ID;
        int size = sizeof(int);
        int data;
    } intPacket;
    
    /* Packet with only pseudo */
    typedef struct {
        int ID;
        int size = sizeof(char)*MAX_PSEUDO_SIZE;
        char pseudo[MAX_PSEUDO_SIZE];
    } pseudoPacket;

//=========================LOGIN PROCESS=================================

    /* Login or register packet */
    typedef struct {
        int ID = LOGIN_REQ_ID;
        int size = sizeof(char)*MAX_PSEUDO_SIZE*2;
        char pseudo[MAX_PSEUDO_SIZE];
        char password[MAX_PSEUDO_SIZE];
    } loginRequestPacket;
    
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
    
    /* Tchat message packet (width*height) */
    typedef struct {
        int ID = TCHAT_MESSAGE_ID;
        int size = sizeof(char)*MESSAGES_MAX_SIZE;
        char msg[MESSAGES_MAX_SIZE];
    } tchatMessagePacket;
    
    /* Player's friends list only */
    typedef struct {
        int ID = FRIENDS_LIST_ID;
        int size = sizeof(char)*MAX_FRIENDS*MAX_PSEUDO_SIZE;
        char friendsList[MAX_FRIENDS*MAX_PSEUDO_SIZE]; /* Every MAX_PSEUDO_SIZE it's a pseudo */
    } friendListPacket;

//=========================GAME=============================================
    
    /* Send all data for sync to the client when turn change */
    typedef struct {
        int ID = TURN_ID;
        typedef struct {
            char pseudo[MESSAGES_MAX_SIZE]; /* Player's name for current turn */
            int life;
            int trash[DECK_SIZE];
            int hand[MAX_HAND];
            int deck[DECK_SIZE];
            int posed[MAX_POSED_CARD];
            int posedLife[MAX_POSED_CARD];
            int ennemyLife;
            int ennemyTrash;
            int ennemyHand;
            int ennemyDeck;
            int ennemyPosed[MAX_POSED_CARD];
            int ennemyPosedLife[MAX_POSED_CARD];
        } turnData;
        int size = sizeof(turnData);
        turnData data;
    } turnPacket;
    
    /* Packet for attack or play spell (or win game) */
    typedef struct {
        int ID;
        typedef struct {
            char pseudo[MESSAGES_MAX_SIZE]; /* Player doing attack or spell or winning */
            int ID; /* monster doing attack or spell */
            int target; /* Target card ID (-1 for player) OR ID for spell card to play (or win card) */
            unsigned finalLife; /* Final life of the target */
        } attackData;
        int size = sizeof(attackData);
        attackData data;
    } attackPacket;
    
    /* Inform about end of the game */
    typedef struct {
        int ID = END_GAME_ID;
        typedef struct {
            int victory; /* -1: lose | 0: nobody | 1: win */
            int card; /* Card he win */
        } winData;
        int size = sizeof(winData);
        winData data;
    } endGamePacket;

//==========================================================================
    
    /* Maximum size of a packets */
    static const int packetMaxSize = sizeof(cardImgPacket);
};

#endif	/* PACKET_HPP */
