#include <string>
#include <vector>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"
#include "Connection.hpp"
#include "Display.hpp"

extern Display *display;

/*TODO Must be define somewhere else */
#define MAX_CARTES 200

namespace PacketManager {
    /* API for other service */
    void managePacket(Packet::packet*);
    void makeLoginRequest(const char*, const char*);
    void makeRegistrationRequest(const char*, const char*);
    void sendDisconnection();
    void requestCollection();
    
    /* receives analyse */
    void loginResult(const Packet::loginResultPacket*);
    void collectionResult(const Packet::collectionListPacket*);
}
