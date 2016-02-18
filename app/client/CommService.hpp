#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"
#include "Connection.hpp"

namespace CommService {
    /* API for other service */
    void managePacket(Packet::packet*);
    void makeLoginRequest(const string, const string);
    void sendDisconnection();
};
