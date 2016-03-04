#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"

#include "Card.hpp"
#include "Collection.hpp"

class Player;
class Game;

namespace PacketManager {
    /* Manage recev packet */
    void manageDisconnectRequest(Player*, Packet::packet*);
    void managNewGameRequest(Player*, Packet::packet*);

    /* API for other service */
    void managePacket(Player*, Packet::packet*);

    /* API in-game */
    void initGame(Player*, std::string);
    void sendCard(Player*, Card*);
    void setTurn(Player*, std::string);
    void sendInfoStartTurn(Player*,int,int);
    void sendAttack(Player*, std::string, int, int, bool, bool, unsigned int);
    void askDefausse(Player*, int);
    void sendEndGame(Player*, bool);
}
