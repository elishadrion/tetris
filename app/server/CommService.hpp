#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"

namespace CommService {
    void manageDisconnectRequest(Packet::packet*);
    void manageLoginRequest(Packet::loginRequestPacket*);
    /* API for other service */
    void managePacket(Packet::packet*);
};
