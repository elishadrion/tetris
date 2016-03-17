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
        ASK_DECK_ID = 53, /* DEFAULT PACKET- ask for deck */
        GAME_START_ID = 54,/* pseudoPacket */
        DECK_CHOOS_ID = 55, /* deckPacket */
        /* CLASSEMENT */
        ASK_CLASSEMENT_ID = 61, /* DEFAULT PACKET */
        SEND_CLASSEMENT_ID = 62, /* ClassementPacket */
        /* GAME PROCESS */
        TURN_ID = 71, /* Signal the current player turn */
        DRAW_ID = 72, /* intPacket */
        ASK_DROP_ID = 73, /* Ask to drop a certain amount of card */
        DROP_ID = 74, /* A packet by droped card (use intPacket) */
        C_ATTACK_ID = 75, /* client - cTwoCardPacket */
        C_PLACE_CARD_ID = 76, /* client - intPacket */
        C_PLACE_SPELL_ID = 77, /* client - cTwoCardPacket */
        C_PLACE_CARD_MAKE_SPELL_ID = 78, /* client - cPlaceCardMakeSpellPacket */
        S_ATTACK_ID = 79, /* server - sAttackPacket */
        S_PLACE_CARD_ID = 80, /* server - sPlaceCardPacket */
        S_PLACE_SPELL_ID = 81, /* server - sAttackPacket */
        S_PLACE_CARD_MAKE_SPELL_ID = 82, /* server - sPlaceCardMakeSpellPacket */
        END_TURN_ID = 83, /* Send to server to signal end of turn (DEFAULT PACKET) */
        QUIT_ID = 84, /* DEFAULT PACKET */
        END_GAME_ID = 85 /* !> use actionPacket */
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

//=========================LOGIN PROCESS==================================

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
            char decks[MAX_DECKS*MAX_DECK_NAME];
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

//=========================GAME===========================================
    
    typedef struct {
        int ID = DECK_CHOOS_ID;
        int size = sizeof(char)*MAX_DECK_NAME;
        char deck[MAX_DECK_NAME];
    } deckPacket;

    /* Send all data for sync to the client when turn change */
    typedef struct {
        int ID = TURN_ID;
        typedef struct {
            bool turn;
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

    typedef struct {
        int ID;
        int size = sizeof(int)*2;
        int cardId; /* Card who make attack */
        int targetCard; /* Card target */
    } cTwoCardPacket;

    typedef struct {
        int ID = C_PLACE_CARD_MAKE_SPELL_ID;
        int size = sizeof(int)*3;
        int idCard;
        int targetCard;
        int placedCard;
    } cPlaceCardMakeSpellPacket;


    typedef struct {
        int ID;
        typedef struct {
            char pseudo[MESSAGES_MAX_SIZE];
            int idCard;
            int targetCard;
            unsigned heal;
        } attackData;
        int size = sizeof(attackData);
        attackData data;
    } sAttackPacket;

    typedef struct {
        int ID = S_PLACE_CARD_ID;
        int size = (sizeof(char)*MESSAGES_MAX_SIZE)+sizeof(int);
        char pseudo[MESSAGES_MAX_SIZE];
        int idCard;
    } sPlaceCardPacket;

    typedef struct {
        int ID = S_PLACE_CARD_MAKE_SPELL_ID;
        typedef struct {
            char pseudo[MESSAGES_MAX_SIZE];
            int idCard;
            int targetCard;
            int placedCard;
            unsigned heal;
        } placeMakeSpellData;
        int size = sizeof(placeMakeSpellData);
        placeMakeSpellData data;
    } sPlaceCardMakeSpellPacket;



//============================ CLASSEMENT ================================

    typedef struct {
        int ID = SEND_CLASSEMENT_ID;
        typedef struct {
            char pseudo[MAX_PSEUDO_SIZE*MAX_PLAYER_CLASSEMENT];
            int victories[MAX_PLAYER_CLASSEMENT];
            int defeats[MAX_PLAYER_CLASSEMENT];
        } classementData;
        int size = sizeof(classementData);
        classementData data;
    } ClassementPacket;

//========================================================================
    
    /* Maximum size of a packets */
    static const int packetMaxSize = sizeof(cardImgPacket);
};

#endif	/* PACKET_HPP */
