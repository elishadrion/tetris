#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"

#include "Card.hpp"
#include "CardMonster.hpp"
#include "Player.hpp"
#include "PlayerInGame.hpp"

typedef struct loginResultStruct {
    std::string pseudo;
    std::string password;
    bool registration;
}

namespace PacketManager {
    /* Manage recev packet */
    void manageDisconnectRequest(Packet::packet*);
    
    loginResultStruct* manageLoginRequest(Packet::loginRequestPacket*); /* SPECIAL function, return directly to connection service */
    Packet::packet* loginResult(int); /* SPECIAL function, return directly to connection service */

    /* API for other service */
    void managePacket(Packet::packet*);
    void initGame(Player*, std::string);
    void sendStartTurnInfo(Player*, dataIGPlayer, std::vector<CardMonster*>, int, int, int);
    void sendCrard(Player*, Card*);
    void setTurn(Player*, std::string);
    void sendAttack(Player*, std::string, int, unsigned int);
    void askDefausse(Player*, int);
    void sendEndGame(Player*, bool);
}
