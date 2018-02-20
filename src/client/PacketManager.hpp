#include <string>
#include <vector>

#include "../common/Constants.hpp"
#include "../common/Packet.hpp"
#include "../common/WizardLogger.hpp"
#include "Connection.hpp"
#include "WizardDisplay.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "CacheManager.hpp"

extern WizardDisplay *display;

namespace PacketManager {
    void manage_packet(void*);


    ///// Login process /////
    // Recev
    void player_info(const Packet::playerInfoPacket*); /* PLAYER_INFO_ID */
    void login_complete(const Packet::packet*); /* LOGIN_COMPLETE_ID */
    // Send
    void send_login_request(const char*, const char*); /* LOGIN_REQ_ID */
    void send_signup_request(const char*, const char*); /* REGIST_REQ_ID */
    void send_disconnect_request(); /* DISCONNECT_ID */




}
