#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"

class CommService {
    void manageDisconnectRequest(Packet::packet*);
    void manageLoginRequest(Packet::loginRequestPacket*);
public:
    /* API for other service */
    void managePacket(Packet::packet*);
};
