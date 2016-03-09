#include <string>

#include "common/Constants.hpp"
#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"
#include "Connection.hpp"
#include "Card.hpp"
#include "WizardDisplay.hpp"
#include "CacheManager.hpp"

extern WizardDisplay *wizardDisplay;

namespace PacketManager {
    /* API for other service */
    void managePacket(Packet::packet*);
    void makeLoginRequest(const char*, const char*);
    void makeRegistrationRequest(const char*, const char*);
    void sendDisconnection();
    void manageFriend(const char*, bool);
    void requestCard(unsigned);
    void registerAsPlayer();
    void cancelWaiting();
    
    /* receives analyse */
    void loginResult(const Packet::loginResultPacket*);
    void playerInfo(const Packet::playerInfoPacket*);
    void getCard(const Packet::cardInfosPacket*);
    void askDeck(const Packet::tchatManagPacket*);
}
