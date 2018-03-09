#ifndef PACKET_HPP
#define	PACKET_HPP

#include <string>



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
        CHAT_USERS_ID = 20,
        CHAT_LOGOUT = 21,

    };
    

};

#endif	/* PACKET_HPP */
