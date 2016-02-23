#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"
#include "Connection.hpp"

namespace PacketManager {
    /* API for other service */
    void managePacket(Packet::packet*);
    void makeLoginRequest(const char*, const char*);
    void makeRegistrationRequest(const char*, const char*);
    void sendDisconnection();
    
    /* receives analyse */
    void loginResult(const Packet::loginResultPacket*);
}
