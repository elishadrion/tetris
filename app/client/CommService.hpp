#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"
#include "Connection.hpp"

namespace CommService {
    /* API for other service */
    void managePacket(Packet::packet*);
    void makeLoginRequest(const char*, const char*);
    void makeRegistrationRequest(const char*, const char*);
    void sendDisconnection();
    
    /* recv analyse */
    void loginResult(const Packet::loginResultPacket*);
};
