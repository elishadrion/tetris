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
    void requestCollection();
    void manageFriend(const char*, bool);
    void askFriendsList();
    
    /* receives analyse */
    void loginResult(const Packet::loginResultPacket*);
    void collectionResult(const Packet::collectionListPacket*);
}
