#include <string>

#include "common/Constants.hpp"
#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"
#include "Connection.hpp"
#include "Card.hpp"
#include "Display.hpp"
#include "CacheManager.hpp"

extern Display *display;

namespace PacketManager {
    /* API for other service */
    void managePacket(Packet::packet*);
    void makeLoginRequest(const char*, const char*);
    void makeRegistrationRequest(const char*, const char*);
    void sendDisconnection();
    void manageFriend(const char*, bool);
    void requestCard(unsigned);
    
    /* receives analyse */
    void loginResult(const Packet::loginResultPacket*);
    void playerInfo(const Packet::playerInfoPacket*);
    void getCard(const Packet::cardInfosPacket*);
}
