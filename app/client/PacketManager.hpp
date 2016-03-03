#include <string>
#include <vector>

#include "common/Constants.hpp"
#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"
#include "Connection.hpp"
#include "Display.hpp"

extern Display *display;

namespace PacketManager {
    /* API for other service */
    void managePacket(Packet::packet*);
    void makeLoginRequest(const char*, const char*);
    void makeRegistrationRequest(const char*, const char*);
    void sendDisconnection();
    void manageFriend(const char*, bool);
    
    /* receives analyse */
    void loginResult(const Packet::loginResultPacket*);
}
