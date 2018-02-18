#include <string>

#include "../common/Packet.hpp"
#include "PlayerManager.hpp"

class Player;
#include "Player.hpp"

namespace PacketManager {
    void manage_packet(Player*, Packet::packet*);
    
    //=============================RECEV=====================================
    
    /* Login process */
    void manage_disconnect_request(Player*, Packet::packet*); /* DISCONNECT_ID */
    
    //===========================SEND==========================================


    void sendError(Player*);

}
