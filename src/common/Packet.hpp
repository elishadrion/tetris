#ifndef PACKET_HPP
#define	PACKET_HPP

#include <string>

#include "Constants.hpp"

class Packet {
public:
    enum IDList {
    	ERROR_ID = 100,
        LOGIN_REQ_ID = 1, /* DEFAULT PACKET */
        REGIST_REQ_ID = 2, /* DEFAULT PACKET */
        LOGIN_ERROR_ID = 3, /* Error code to convert in message (intPacket) */
        PLAYER_INFO_ID = 4, /* Success so get all player infos needed */
        LOGIN_COMPLETE_ID = 5, /* DEFAULT PACKET */
        DISCONNECT_ID = 6, /* DEFAULT PACKET */
        PLAY_REQUEST_ID = 7,
        GAME_WAITING_ID = 8,
        GAME_READY_ID = 9,
        MOVE_TETRIMINOS_RIGHT = 10,
        MOVE_TETRIMINOS_LEFT = 11,
        MOVE_TETRIMINOS_HOLD = 12,
        MOVE_TETRIMINOS_HDROP = 13,
        MOVE_TETRIMINOS_DROP = 14,
        MOVE_TETRIMINOS_TURN_RIGHT = 15,
        MOVE_TETRIMINOS_TURN_LEFT = 16,
        MOVE_TETRIMINOS = 17,
        CHAT_MESSAGE_ID = 18,
        CHAT_MESSAGE_CONN = 19,

    };
    
    /* Default size of all packets (without data) */
    static const int packetSize = sizeof(int);
    
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
        int ID = 0;
        int size = (sizeof(char)*MAX_PSEUDO_SIZE)+sizeof(int);
        char pseudo[MAX_PSEUDO_SIZE];
        int data;
    } pseudoIntPacket;


//=========================LOGIN PROCESS==================================

    /* Login or register packet */
    typedef struct {
        int ID = LOGIN_REQ_ID;
        int size = sizeof(char)*MAX_PSEUDO_SIZE + (sizeof(char)*HASH_SIZE);
        char username[MAX_PSEUDO_SIZE];
        char password[HASH_SIZE];
        int sockfd;
    } loginRequestPacket;

    /* Player info (sucess login) */
    typedef struct {
        int ID = PLAYER_INFO_ID;
        typedef struct {
            char pseudo[MAX_PSEUDO_SIZE];
            unsigned victories;
            unsigned defeats;
        } playerData;
        int size = sizeof(playerData);
        playerData data; /* We define it but we must include it */
    } playerInfoPacket;
    
//=========================JEU==================================

    typedef struct {
        int ID = PLAY_REQUEST_ID;
        int size = sizeof(int)*2;
        int mode;
        int socket;
    } playRequestPacket;

    typedef struct {
        int ID = GAME_READY_ID;
        int size = sizeof(int) + sizeof(unsigned);
        int data;
        unsigned seed;
    } playApprovalPacket;

//=========================CHAT==================================
    typedef struct {
        int ID = CHAT_MESSAGE_ID;
        int size = (sizeof(char)*MAX_MESSAGE_SIZE)+(sizeof(char)*MAX_PSEUDO_SIZE*10);
        char sender[MAX_PSEUDO_SIZE];
        char message[MAX_MESSAGE_SIZE];
        
    } chatMessagePacket;

    static const int packetMaxSize = sizeof(playerInfoPacket);

};

#endif	/* PACKET_HPP */
