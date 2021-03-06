#ifndef PACKETMANAGER_HPP
#define PACKETMANAGER_HPP

#include <string>

#include "../common/Packet.hpp"
#include "../common/WizardLogger.hpp"

#include "Player.hpp"
#include "PlayerManager.hpp"
#include "Global.hpp"

namespace PacketManager {

    void manage_packet(Player*, void*);
    //=============================RECEPTION=====================================
    void manage_disconnect_request(Player*);
    //Gère une demande de login
	Player* manage_login_request(Packet::loginRequestPacket*);
    //Gère la demande d'un joueur à jouer
    Player* manage_signup_request(Packet::loginRequestPacket*);
	void manage_play_request(Player*, Packet::playRequestPacket*);
    //Gère le déplacement d'un tetriminos du joueur
    void manage_move_tetriminos_request(Player*, Packet::intPacket*);
    //Chat
    void receive_chat_connection(Player*, Packet::pseudoPacket*);
    void receive_chat_message(Player*, Packet::chatMessagePacket*);
    void receive_logout_chat(Player*);
    //===========================ENVOI==========================================
    //Signale au joueur que sa partie est en préparation
	  void send_game_waiting(Player*);
    //Signale au joueur que sa partie et prête, et lance
    void transmit_chat_message(Packet::chatMessagePacket*);
	void send_game_ready(Player*, unsigned);
    void send_error(Player*);
    void receive_friend_request(Player* player, Packet::friendRequestPacket* packet);
    void receive_stat_request(Player* player, Packet::statisticRequestPacket* packet);
    void send_game_stopping(Player* player) ;

}

#endif
