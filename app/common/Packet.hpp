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
        LOGIN_COMPLETE_ID = 15, /* DEFAULT PACKET */
        DISCONNECT_ID = 16, /* DEFAULT PACKET */
        /* CARDS PROCESS */
        CARTE_INFO_ID = 21, /* Send all card info (no img) */
        CARTE_IMG_REQ_ID = 22, /* intPacket */
        CARTE_IMG_ID = 23, /* intPacket */
        /* TCHAT */
        TCHAT_SEND_MSG_ID = 31, /* tchatSendMsgPacket */
        TCHAT_RECEV_MSG_ID = 32, /* tchatRecevMsgPacket */
        /* FRIEND */
        FRIEND_ADD_ID = 41, /* Get FRIEND_DEL_ID if failed (use pseudoPacket) */
        FRIEND_DEL_ID = 42,  /* pseudoPacket */
        FRIENDS_REQ_ID = 43, /* Do you want to be friend ? (use pseudoPacket) */
        FRIENDS_LIST_REQ_ID = 44, /* DEFAULT PACKET */
        FRIENDS_LIST_ID = 45, /* Send all friendList */
        /* LAUNCHING GAME PROCESS */
        WAITING_ID = 51, /* DEFAULT PACKET */
        CANCEL_ID = 52, /* DEFAULT PACKET */
        ASK_DECK_AND_PSEUDO_ID = 53, /* pseudoPacket - ask for deck and inform pseudo */
        DECK_CHOOS_ID = 54, /* deckPacket */
        /* CLASSEMENT */
        ASK_CLASSEMENT_ID = 61, /* DEFAULT PACKET */
        SEND_CLASSEMENT_ID = 62, /* ClassementPacket */
        /* GAME PROCESS */
        TURN_ID = 71, /* Signal the current player turn */
        BEGIN_DRAW_ID = 72, // When the game start - drawPacket
        DRAW_ID = 73, /* intPacket */
        ADVERSE_DRAW_ID = 74, // Adverse player draw a card - DEFAULT PACKET
        ASK_DROP_ID = 75, /* Ask to drop a certain amount of card */
        DROP_ID = 76, /* A packet by droped card (use intPacket) */
        C_ATTACK_ID = 77, // client - twoCardPacket
        C_PLACE_CARD_ID = 78, // client - intPacket
        C_PLACE_CARD_MAKE_SPELL_ID = 79, // client - twoCardPacket
        S_ATTACK_ID = 80, // server - attackPacket
        S_PLACE_SPELL_ID = 81, // server - placeAttackSpellPacket
        S_PLACE_CARD_ID = 82, // server - placeCardPacket
        S_PLACE_CARD_AND_ATTACK_ID = 83, // server - placeAttackPacket
        PLAYER_DAMAGE_ID = 84, /* damage when player havent card in deck - pseudoIntPacket */
        END_TURN_ID = 85, /* Send to server to signal end of turn (DEFAULT PACKET) */
        QUIT_ID = 86, /* DEFAULT PACKET */
        END_GAME_ID = 87, /* !> use actionPacket */
        // ERROR
        ERROR_ID = 100 /* intPacket */
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

    typedef struct {
        int ID = S_PLACE_CARD_ID;
        int size = (sizeof(char)*MAX_PSEUDO_SIZE)+sizeof(int);
        char pseudo[MAX_PSEUDO_SIZE];
        int data;
    } pseudoIntPacket;


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
            char name[MAX_CARD_NAME];
            char description[MAX_DESCRITION_SIZE];
            unsigned energyCost;
            unsigned maxHP;
            unsigned attack;
            // TO DO: effect ?
        } cardData;
        int size = sizeof(cardData);
        cardData data; /* We define it but we must include it */
    } cardInfosPacket;
    
    typedef struct {
        int ID = CARTE_IMG_ID;
        int size = 95000; /* Max size is currently 95Ko */
        void* data[95000]; /* Must be complete image binary data */
    } cardImgPacket;

//====================TCHAT & FRIEND PROCESS==============================
    
    /* Tchat message packet (width*height) */
    typedef struct {
        int ID = TCHAT_SEND_MSG_ID;
        int size = sizeof(char)*(MESSAGES_MAX_SIZE+MAX_PSEUDO_SIZE);
        char pseudoTo[MAX_PSEUDO_SIZE];
        char msg[MESSAGES_MAX_SIZE];
    } tchatSendMsgPacket;

    typedef struct {
        int ID = TCHAT_RECEV_MSG_ID;
        int size = sizeof(char)*(MESSAGES_MAX_SIZE+2*MAX_PSEUDO_SIZE);
        char pseudoFrom[MAX_PSEUDO_SIZE];
        char pseudoTo[MAX_PSEUDO_SIZE];
        char msg[MESSAGES_MAX_SIZE];
    } tchatRecevMsgPacket;
    
    /* Player's friends list only */
    typedef struct {
        int ID = FRIENDS_LIST_ID;
        int size = sizeof(char)*MAX_FRIENDS*MAX_PSEUDO_SIZE;
        char friendsList[MAX_FRIENDS*MAX_PSEUDO_SIZE]; /* Every MAX_PSEUDO_SIZE it's a pseudo */
    } friendListPacket;


// ============================= GAME =====================================
    
    typedef struct {
        int ID = DECK_CHOOS_ID;
        int size = sizeof(char)*MAX_DECK_NAME;
        char deck[MAX_DECK_NAME];
    } deckPacket;

    /* Send information to tell about the player turn */
    typedef struct {
        int ID = TURN_ID;
        int size = sizeof(int)+sizeof(bool);
        bool isTurn;
        unsigned nbrTurn;
    } turnPacket;

    typedef struct {
        int ID = BEGIN_DRAW_ID;
        int size = sizeof(unsigned)*(MIN_CARD_IN_HAND+1);
        unsigned listID[MIN_CARD_IN_HAND];
        unsigned min_hand = MIN_CARD_IN_HAND;
    } beginDrawPacket;

    
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
        int cardOne; /* Card1 */
        int cardTwo; /* Card2 */
    } twoCardPacket;

    typedef struct {
        int ID = S_ATTACK_ID;
        typedef struct {
            char pseudo[MAX_PSEUDO_SIZE];
            int cardPosition;
            unsigned cardHeal;
            int targetPosition;
            unsigned targetHeal;
        } attackData;
        int size = sizeof(attackData);
        attackData data;
    } attackPacket;

    typedef struct {
        int ID = S_PLACE_SPELL_ID;
        typedef struct {
            char pseudo[MAX_PSEUDO_SIZE];
            int idCard;
            int targetPosition;
            unsigned heal;
            unsigned attack;
        } placeAttackSpellData;
        int size = sizeof(placeAttackSpellData);
        placeAttackSpellData data;
    } placeAttackSpellPacket;

    typedef struct {
        int ID = S_PLACE_CARD_AND_ATTACK_ID;
        typedef struct {
            char pseudo[MAX_PSEUDO_SIZE];
            int idCard;
            int cardPosition;
            int targetPosition;
            unsigned heal;
            unsigned attack;
        } placeAttackData;
        int size = sizeof(placeAttackData);
        placeAttackData data;
    } placeAttackPacket;

    typedef struct {
        int ID = Packet::S_PLACE_CARD_ID;
        int size = sizeof(char)*MAX_PSEUDO_SIZE + 2*sizeof(int);
        char pseudo[MAX_PSEUDO_SIZE];
        int idCard;       // Id of the new card
        int cardPosition; // Position on the board of the new card
    } placeCardPacket;



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
    } classementPacket;


//========================================================================
    
    /* Maximum size of a packets */
    static const int packetMaxSize = sizeof(cardImgPacket);
};

#endif	/* PACKET_HPP */
