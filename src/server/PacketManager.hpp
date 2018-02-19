#ifndef PACKETMANAGER_HPP
#define PACKETMANAGER_HPP
#include <string>

#include "../common/Packet.hpp"
#include "PlayerManager.hpp"
#include "../common/WizardLogger.hpp"

class Player;
#include "Player.hpp"

namespace PacketManager {
    void manage_packet(Player*, void*);
    
    //=============================RECEV=====================================
    
    /* Login process */
    void manage_disconnect_request(Player*, Packet::packet*); /* DISCONNECT_ID */
	Player* manage_login_request(Packet::loginRequestPacket*);


    //===========================SEND==========================================


    void sendError(Player*);

}

#endif
