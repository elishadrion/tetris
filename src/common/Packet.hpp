#ifndef PACKET_HPP
#define	PACKET_HPP

#include <string>

#include "Constants.hpp"

class Packet {
public:
    /* All packet ID */
    enum IDList {
    	ERROR_ID = 100,
        /* LOGIN PROCESS (all but the last in a mini-feature) */
        LOGIN_REQ_ID = 1, /* DEFAULT PACKET */
        REGIST_REQ_ID = 2, /* DEFAULT PACKET */
        LOGIN_RES_ID = 3, /* Error code to convert in message (intPacket) */
        PLAYER_INFO_ID = 4, /* Success so get all player infos needed */
        LOGIN_COMPLETE_ID = 5, /* DEFAULT PACKET */
        DISCONNECT_ID = 6, /* DEFAULT PACKET */
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
        int ID = 0;
        int size = (sizeof(char)*MAX_PSEUDO_SIZE)+sizeof(int);
        char pseudo[MAX_PSEUDO_SIZE];
        int data;
    } pseudoIntPacket;


//=========================LOGIN PROCESS==================================

    /* Login or register packet */
    typedef struct {
        int ID = LOGIN_REQ_ID;
        int size = sizeof(char)*MAX_PSEUDO_SIZE + sizeof(char)*HASH_SIZE;
        char username[MAX_PSEUDO_SIZE];
        char password[HASH_SIZE];
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
    
    //static const int packetMaxSize = sizeof(playerInfoPacket);
    static const int packetMaxSize = sizeof(playerInfoPacket);

};

#endif	/* PACKET_HPP */
