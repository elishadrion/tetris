#ifndef PACKETMANAGER_HPP
#define PACKETMANAGER_HPP


#include <string>
#include <vector>

#include "SalonChat.hpp"
#include "StatisticsManager.hpp"
#include "FriendsManager.hpp"

#include "../common/Constants.hpp"
#include "../common/Packet.hpp"
#include "../common/WizardLogger.hpp"
#include "Connection.hpp"
#include "WizardDisplay.hpp"
#include "Player.hpp"



extern WizardDisplay *display;
extern GameManager* game_manager;
extern Connection *conn;
extern FriendsManager *friends_manager;
extern StatisticsManager *statistics_manager;

extern SalonChat* salon_chat;


namespace PacketManager {
    void manage_packet(void*);


    //=============================RECEPTION=====================================
    void player_info(const Packet::playerInfoPacket*); /* PLAYER_INFO_ID */
    //login accepté par le serveur
    void login_complete(); /* LOGIN_COMPLETE_ID */
    //Serveur signale qu'il ya eu une erreur durant le lgoin
    void login_error();
    //Partie en préparation pour le joueur
    void game_waiting();
    //Partie prête
    void game_ready(Packet::playApprovalPacket*);
    void manage_move_tetriminos_request(Packet::intPacket*);

    //=============================CHAT=====================================

    void receive_chat_message(Packet::chatMessagePacket*);
    void send_chat_conn(const char*);
    void send_chat_message(const char*, const char*);
    void receive_users_name(Packet::usersInChatPacket*);
    void send_logout_chat();
    //=============================ENVOI=====================================
    //===================LOGIN & SIGNUP===========================
    //Demande à se connecter
    void send_login_request(const char*, const char*); /* LOGIN_REQ_ID */
    //Demande à s'inscrire
    void send_signup_request(const char*, const char*); /* REGIST_REQ_ID */
    //Demande à jouer
    void send_play_request(int);
    void send_disconnect_request(); /* DISCONNECT_ID */
    //===================JEU===========================
    void send_move_tetriminos(int);

    //===================FRIENDS==========================
    void send_friend_request(int action_type, const char *friend_name);

    void send_stat_request(int action_type);

    void receive_users_list(Packet::usersPacket* packet);

    void game_stop_now();
}

#endif
