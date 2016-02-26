#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"

#include "Card.hpp"
#include "Collection.hpp"
#include "Player.hpp"

class Player;

namespace PacketManager {
    /* Manage recev packet */
    void manageDisconnectRequest(Player*, Packet::packet*);
    void manageCollectionRequest(Player*, Packet::packet*);

    /* API for other service */
    void managePacket(Player*, Packet::packet*);

    /* API in-game */
    void initGame(Player*, std::string);
    void sendStartTurnInfo(Player*, std::vector<Card*>, int, int, int);
    void sendCard(Player*, Card*);
    void setTurn(Player*, std::string);
    void sendInfoStartTurn(Player*,int,int);
    void sendAttack(Player*, std::string, int, int, bool, bool, unsigned int);
    void askDefausse(Player*, int);
    void sendEndGame(Player*, bool);
}
